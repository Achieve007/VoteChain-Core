// src/Blockchain.cpp
// Implementation of Blockchain class - the heart of our voting system

#include "Blockchain.h"
#include <iostream>

// Constructor: Initialize blockchain with genesis block
Blockchain::Blockchain() {
    // Create and add the genesis block (the foundation)
    chain.push_back(Block::createGenesisBlock());
}

// Returns the most recently added block
Block Blockchain::getLatestBlock() const {
    return chain.back();
}

// Adds a new block to the blockchain
// Automatically links it to the previous block's hash
void Blockchain::addBlock(Block newBlock) {
    // Security check: Ensure the new block references the correct previous hash
    if (newBlock.getPreviousHash() != getLatestBlock().getHash()) {
        std::cerr << "ERROR: Block's previous hash doesn't match chain!" << std::endl;
        std::cerr << "Expected: " << getLatestBlock().getHash() << std::endl;
        std::cerr << "Got: " << newBlock.getPreviousHash() << std::endl;
        return;
    }
    
    // Add block to the chain
    chain.push_back(newBlock);
    
    std::cout << "✓ Block #" << newBlock.getIndex() 
              << " added successfully to the blockchain" << std::endl;
}

// Validates and adds a vote to a pending block
// Performs comprehensive validation including duplicate detection across entire chain
// Time Complexity: O(n*m) where n = number of blocks, m = average votes per block
bool Blockchain::addVoteToPendingBlock(Block& pendingBlock, const Vote& vote) {
    // Step 1: Validate vote fields
    if (!vote.isValid()) {
        std::cerr << "✗ Vote rejected: Invalid vote data (empty fields)" << std::endl;
        return false;
    }
    
    // Step 2: Check for duplicate voter ID across entire blockchain
    // This is the critical security check to prevent double-voting
    if (hasVoterVoted(vote.getVoterTempID())) {
        std::cerr << "✗ Vote rejected: Voter " << vote.getVoterTempID() 
                  << " has already voted in the blockchain" << std::endl;
        return false;
    }
    
    // Step 3: Check if voter already voted in the pending block
    if (pendingBlock.hasVoter(vote.getVoterTempID())) {
        std::cerr << "✗ Vote rejected: Voter " << vote.getVoterTempID() 
                  << " already voted in this pending block" << std::endl;
        return false;
    }
    
    // Step 4: Add vote to pending block
    if (pendingBlock.addVote(vote)) {
        std::cout << "✓ Vote accepted: " << vote.getVoterTempID() 
                  << " -> " << vote.getCandidate() << std::endl;
        return true;
    }
    
    return false;
}

// Scans entire blockchain to check if a voter has already cast a vote
// This prevents double-voting - a critical security feature
// Time Complexity: O(n*m) where n = blocks in chain, m = avg votes per block
// Trade-off: Slower validation for stronger security guarantee
bool Blockchain::hasVoterVoted(const std::string& voterTempID) const {
    // Scan every block in the chain
    for (const auto& block : chain) {
        // Scan every vote in each block
        for (const auto& vote : block.getVotes()) {
            if (vote.getVoterTempID() == voterTempID) {
                return true;  // Voter found - they already voted!
            }
        }
    }
    return false;  // Voter not found - they haven't voted yet
}

// Validates the entire blockchain integrity
// Checks: (1) Each block's hash is valid, (2) Each block links to previous correctly
bool Blockchain::isChainValid() const {
    // Start from block 1 (skip genesis block in linking check)
    for (size_t i = 1; i < chain.size(); i++) {
        const Block& currentBlock = chain[i];
        const Block& previousBlock = chain[i - 1];
        
        // Check 1: Is the current block's hash valid?
        if (!currentBlock.isValid()) {
            std::cout << "✗ Block #" << currentBlock.getIndex() 
                      << " has invalid hash!" << std::endl;
            return false;
        }
        
        // Check 2: Does current block properly reference previous block?
        if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
            std::cout << "✗ Block #" << currentBlock.getIndex() 
                      << " has broken chain link!" << std::endl;
            std::cout << "  Expected previous hash: " << previousBlock.getHash() << std::endl;
            std::cout << "  Got: " << currentBlock.getPreviousHash() << std::endl;
            return false;
        }
    }
    
    // Also validate genesis block
    if (!chain[0].isValid()) {
        std::cout << "✗ Genesis block is invalid!" << std::endl;
        return false;
    }
    
    return true;
}

// Returns read-only reference to the entire chain
const std::vector<Block>& Blockchain::getChain() const {
    return chain;
}

// Display entire blockchain with validation
void Blockchain::display() const {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║        BLOCKCHAIN VOTING SYSTEM        ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
    std::cout << "Chain Length: " << chain.size() << " blocks" << std::endl;
    std::cout << "Total Votes: " << getTotalVotes() << std::endl;
    std::cout << "Chain Valid: " << (isChainValid() ? "✓ YES" : "✗ NO") << std::endl;
    
    // Display each block
    for (const auto& block : chain) {
        block.display();
    }
}

// Returns number of blocks in the chain
int Blockchain::getChainLength() const {
    return static_cast<int>(chain.size());
}

// Counts total votes across all blocks
int Blockchain::getTotalVotes() const {
    int total = 0;
    for (const auto& block : chain) {
        total += static_cast<int>(block.getVotes().size());
    }
    return total;
}