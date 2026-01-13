// include/VotingAPI.h
// REST API endpoints for blockchain voting system
// Uses Crow C++ web framework

#ifndef VOTING_API_H
#define VOTING_API_H

#include "Blockchain.h"
#include "Block.h"
#include "Vote.h"
#include "VoteValidator.h"
#include <crow.h>
#include <string>
#include <mutex>

#ifdef ERROR
#undef ERROR
#endif

// API response status codes
enum class APIStatus {
    SUCCESS,        // Vote accepted and added to blockchain
    DUPLICATE,      // Vote rejected - voter already voted
    INVALID,        // Vote rejected - invalid fields
    ERROR           // Server error
};

// API response structure
struct APIResponse {
    APIStatus status;
    std::string message;
    std::string voterTempID;
    std::string candidate;
    int blockIndex;
    std::string blockHash;
    std::time_t timestamp;
    std::string rejectionReason;
    double processingTimeMs;
    
    // Convert to JSON
    crow::json::wvalue toJSON() const;
};

// Voting API Handler
class VotingAPI {
private:
    Blockchain& blockchain;              // Reference to blockchain instance
    Block* currentBlock;                 // Current pending block
    int nextBlockIndex;                  // Next block index
    std::mutex blockMutex;              // Thread safety for concurrent requests
    
    // Statistics
    int totalVotesReceived;
    int totalVotesAccepted;
    int totalVotesRejected;
    
    // Helper methods
    APIResponse processVote(const std::string& voterID, 
                           const std::string& candidate,
                           std::time_t timestamp = 0);
    void finalizeCurrentBlock();
    bool shouldFinalizeBlock() const;

public:
    // Constructor
    VotingAPI(Blockchain& chain);
    
    // Destructor
    ~VotingAPI();
    
    // API Endpoints
    crow::json::wvalue handleAddVote(const crow::request& req);
    crow::json::wvalue handleGetStats(const crow::request& req);
    crow::json::wvalue handleGetBlock(const crow::request& req, int blockIndex);
    crow::json::wvalue handleGetDeadBlock(const crow::request& req);
    crow::json::wvalue handleValidateChain(const crow::request& req);
    
    // Configuration
    static const int MAX_VOTES_PER_BLOCK = 100;
};

#endif // VOTING_API_H