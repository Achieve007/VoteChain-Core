// src/VotingAPI.cpp
// Implementation of REST API endpoints

#include "VotingAPI.h"
#include <chrono>
#include <iostream>

// Constructor
VotingAPI::VotingAPI(Blockchain& chain) 
    : blockchain(chain), nextBlockIndex(1), 
      totalVotesReceived(0), totalVotesAccepted(0), totalVotesRejected(0) {
    
    // Create first pending block
    std::string previousHash = blockchain.getChain().back().getHash();
    currentBlock = new Block(nextBlockIndex, previousHash);
    
    std::cout << "Voting API initialized. Ready to accept votes." << std::endl;
}

// Destructor
VotingAPI::~VotingAPI() {
    // Finalize any pending block
    if (currentBlock && currentBlock->getVotes().size() > 0) {
        finalizeCurrentBlock();
    }
    delete currentBlock;
}

// Convert APIResponse to JSON
crow::json::wvalue APIResponse::toJSON() const {
    crow::json::wvalue response;
    
    // Status string
    std::string statusStr;
    switch (status) {
        case APIStatus::SUCCESS:   statusStr = "success"; break;
        case APIStatus::DUPLICATE: statusStr = "duplicate"; break;
        case APIStatus::INVALID:   statusStr = "invalid"; break;
        case APIStatus::ERROR:     statusStr = "error"; break;
    }
    
    response["status"] = statusStr;
    response["message"] = message;
    
    // Data object
    crow::json::wvalue dataObj;
    dataObj["voterTempID"] = voterTempID;
    dataObj["candidate"] = candidate;
     dataObj["blockIndex"] = (blockIndex >= 0) ? blockIndex : crow::json::wvalue();
    dataObj["blockHash"] = (blockHash.empty()) ? nullptr : blockHash;
    dataObj["timestamp"] = static_cast<long long>(timestamp);
    
    if (!rejectionReason.empty()) {
        dataObj["rejectionReason"] = rejectionReason;
    }
    
    response["data"] = std::move(dataObj);
    
    // Meta object
    crow::json::wvalue metaObj;
    metaObj["processingTime"] = processingTimeMs;
    metaObj["serverTimestamp"] = static_cast<long long>(std::time(nullptr));
    response["meta"] = std::move(metaObj);
    
    return response;
}

// Process vote submission
APIResponse VotingAPI::processVote(const std::string& voterID, 
                                   const std::string& candidate,
                                   std::time_t timestamp) {
    APIResponse response;
    response.voterTempID = voterID;
    response.candidate = candidate;
    response.timestamp = (timestamp > 0) ? timestamp : std::time(nullptr);
    response.blockIndex = -1;
    response.blockHash = "";
    
    // Create vote object
    Vote vote(voterID, candidate, response.timestamp);
    
    // Attempt to add to blockchain
    bool success = blockchain.addVoteToPendingBlock(*currentBlock, vote);
    
    if (success) {
        // Vote accepted
        response.status = APIStatus::SUCCESS;
        response.message = "Vote successfully recorded";
        response.blockIndex = currentBlock->getIndex();
        response.blockHash = currentBlock->getHash();
        totalVotesAccepted++;
        
        // Check if block should be finalized
        if (shouldFinalizeBlock()) {
            finalizeCurrentBlock();
        }
    } else {
        // Vote rejected - determine reason
        totalVotesRejected++;
        
        // Check if it's a duplicate
        if (blockchain.hasVoterVoted(voterID)) {
            response.status = APIStatus::DUPLICATE;
            response.message = "Vote rejected: Voter has already voted";
            response.rejectionReason = "Duplicate voter ID detected in blockchain";
        } else {
            // Must be invalid format
            response.status = APIStatus::INVALID;
            response.message = "Vote rejected: Invalid vote data";
            
            // Determine specific reason
            ValidationResult voterResult = VoteValidator::validateVoterID(voterID);
            if (!voterResult.isValid) {
                response.rejectionReason = voterResult.errorMessage;
            } else {
                ValidationResult candidateResult = VoteValidator::validateCandidate(candidate);
                response.rejectionReason = candidateResult.errorMessage;
            }
        }
    }
    
    return response;
}

// Check if current block should be finalized
bool VotingAPI::shouldFinalizeBlock() const {
    return currentBlock->getVotes().size() >= MAX_VOTES_PER_BLOCK;
}

// Finalize current block and create new one
void VotingAPI::finalizeCurrentBlock() {
    std::cout << "Finalizing block #" << currentBlock->getIndex() 
              << " with " << currentBlock->getVotes().size() << " votes" << std::endl;
    
    // Add block to blockchain
    blockchain.addBlock(*currentBlock);
    
    // Create new pending block
    delete currentBlock;
    nextBlockIndex++;
    std::string previousHash = blockchain.getChain().back().getHash();
    currentBlock = new Block(nextBlockIndex, previousHash);
}

// POST /addVote - Main endpoint
crow::json::wvalue VotingAPI::handleAddVote(const crow::request& req) {
    auto startTime = std::chrono::high_resolution_clock::now();
    
    std::lock_guard<std::mutex> lock(blockMutex);
    totalVotesReceived++;
    
    try {
        // Parse JSON request
        auto jsonBody = crow::json::load(req.body);
        if (!jsonBody) {
            APIResponse response;
            response.status = APIStatus::ERROR;
            response.message = "Invalid JSON format";
            response.timestamp = std::time(nullptr);
            
            auto endTime = std::chrono::high_resolution_clock::now();
            response.processingTimeMs = std::chrono::duration<double, std::milli>(
                endTime - startTime).count();
            
            return response.toJSON();
        }
        
        // Extract fields
        std::string voterID = jsonBody["voterTempID"].s();
        std::string candidate = jsonBody["candidate"].s();
        std::time_t timestamp = jsonBody.has("timestamp") ? 
            jsonBody["timestamp"].i() : 0;
        
        // Process vote
        APIResponse response = processVote(voterID, candidate, timestamp);
        
        // Calculate processing time
        auto endTime = std::chrono::high_resolution_clock::now();
        response.processingTimeMs = std::chrono::duration<double, std::milli>(
            endTime - startTime).count();
        
        return response.toJSON();
        
    } catch (const std::exception& e) {
        APIResponse response;
        response.status = APIStatus::ERROR;
        response.message = std::string("Server error: ") + e.what();
        response.timestamp = std::time(nullptr);
        
        auto endTime = std::chrono::high_resolution_clock::now();
        response.processingTimeMs = std::chrono::duration<double, std::milli>(
            endTime - startTime).count();
        
        return response.toJSON();
    }
}

// GET /stats - Statistics endpoint
crow::json::wvalue VotingAPI::handleGetStats(const crow::request& req) {
    std::lock_guard<std::mutex> lock(blockMutex);
    
    crow::json::wvalue response;
    response["totalVotesReceived"] = totalVotesReceived;
    response["totalVotesAccepted"] = totalVotesAccepted;
    response["totalVotesRejected"] = totalVotesRejected;
    response["currentBlockIndex"] = currentBlock->getIndex();
    response["votesInCurrentBlock"] = static_cast<int>(currentBlock->getVotes().size());
    response["totalBlocks"] = blockchain.getChainLength();
    response["totalVotesInChain"] = blockchain.getTotalVotes();
    response["chainValid"] = blockchain.isChainValid();
    
    return response;
}

// GET /block/:index - Get specific block
crow::json::wvalue VotingAPI::handleGetBlock(const crow::request& req, int blockIndex) {
    std::lock_guard<std::mutex> lock(blockMutex);
    
    crow::json::wvalue response;
    
    if (blockIndex < 0 || blockIndex >= blockchain.getChainLength()) {
        response["status"] = "error";
        response["message"] = "Block index out of range";
        return response;
    }
    
    const Block& block = blockchain.getChain()[blockIndex];
    
    response["status"] = "success";
    response["blockIndex"] = block.getIndex();
    response["blockHash"] = block.getHash();
    response["previousHash"] = block.getPreviousHash();
    response["timestamp"] = static_cast<long long>(block.getTimestamp());
    response["voteCount"] = static_cast<int>(block.getVotes().size());
    
    // Include votes
    std::vector<crow::json::wvalue> votesArray;
    for (const auto& vote : block.getVotes()) {
        crow::json::wvalue voteObj;
        voteObj["voterTempID"] = vote.getVoterTempID();
        voteObj["candidate"] = vote.getCandidate();
        voteObj["timestamp"] = static_cast<long long>(vote.getTimestamp());
        votesArray.push_back(std::move(voteObj));
    }
    response["votes"] = std::move(votesArray);
    
    return response;
}

// GET /deadblock - Get rejected votes
crow::json::wvalue VotingAPI::handleGetDeadBlock(const crow::request& req) {
    std::lock_guard<std::mutex> lock(blockMutex);
    
    const DeadBlock& deadBlock = blockchain.getDeadBlock();
    
    crow::json::wvalue response;
    response["status"] = "success";
    response["totalRejected"] = deadBlock.getTotalRejected();
    response["invalidCount"] = deadBlock.getInvalidCount();
    response["duplicateCount"] = deadBlock.getDuplicateCount();
    
    // Export as JSON
    response["exportJSON"] = deadBlock.toJSON();
    
    return response;
}

// GET /validate - Validate entire chain
crow::json::wvalue VotingAPI::handleValidateChain(const crow::request& req) {
    std::lock_guard<std::mutex> lock(blockMutex);
    
    crow::json::wvalue response;
    bool isValid = blockchain.isChainValid();
    
    response["status"] = "success";
    response["chainValid"] = isValid;
    response["message"] = isValid ? "Blockchain integrity verified" : 
                                    "Blockchain integrity compromised";
    response["totalBlocks"] = blockchain.getChainLength();
    response["totalVotes"] = blockchain.getTotalVotes();
    
    return response;
}