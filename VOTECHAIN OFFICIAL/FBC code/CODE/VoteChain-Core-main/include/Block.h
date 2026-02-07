// include/Block.h
// Represents a single block in the blockchain
// Each block contains multiple votes, references previous block, and has its own hash

#ifndef BLOCK_H
#define BLOCK_H

#include "Vote.h"
#include <vector>
#include <string>
#include <ctime>

// Block class represents a container of votes in the blockchain
class Block {
private:
    int index;                      // Position in the blockchain (0 for genesis)
    std::string previousHash;       // Hash of the previous block (links the chain)
    std::time_t timestamp;          // When this block was created
    std::vector<Vote> votes;        // Collection of votes in this block
    std::string hash;               // This block's hash (computed from all data)
    
    // Private helper: Calculates hash based on block contents
    std::string calculateHash() const;

public:
    // Constructor: Creates a new block with SHA-256 hash
    Block(int idx, const std::string& prevHash);
    
    // Add a vote to this block (before mining/sealing)
    // Returns: true if vote was added, false if validation failed
    bool addVote(const Vote& vote);

    // Check if a voter has already voted in this block
    bool hasVoter(const std::string& voterTempID) const;
    
    // Getters: Provide read-only access to block data
    int getIndex() const;
    std::string getPreviousHash() const;
    std::string getHash() const;
    std::time_t getTimestamp() const;
    const std::vector<Vote>& getVotes() const;
    
    // Validation: Verifies block's hash is correct
    bool isValid() const;
    
    // Display: Pretty-prints block information
    void display() const;
    
    // Static factory method: Creates the first block in the chain
    static Block createGenesisBlock();
};

#endif // BLOCK_H