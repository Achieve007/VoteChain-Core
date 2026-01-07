#ifndef BLOCK_H
#define BLOCK_H

#include "Vote.h"
#include <vector>
#include <string>
#include <ctime>

// Block class represents a container of votes in the blockchain
class Block {
private:
    int index;                      // Position in blockchain
    std::string previousHash;       // Hash of previous block (chain linkage)
    time_t timestamp;               // When block was created
    std::vector<Vote> votes;        // Collection of votes in this block
    std::string hash;               // This block's hash

    // Private helper: calculate hash for this block
    std::string calculateHash() const;

public:
    // Constructor
    Block(int idx, const std::string& prevHash);
    
    // Add vote to block
    void addVote(const Vote& vote);
    
    // Getters
    int getIndex() const;
    std::string getPreviousHash() const;
    std::string getHash() const;
    time_t getTimestamp() const;
    const std::vector<Vote>& getVotes() const;
    
    // Display block information
    void display() const;
};

#endif // BLOCK_H