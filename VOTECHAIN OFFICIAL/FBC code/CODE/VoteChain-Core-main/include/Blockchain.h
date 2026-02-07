// include/Blockchain.h
// Manages the entire blockchain: creates, validates, and maintains the chain
// Ensures immutability and cryptographic integrity of the voting system
// Includes DeadBlock system for rejected vote tracking

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include "DeadBlock.h"
#include <vector>

class Blockchain {
private:
    std::vector<Block> chain;       // The complete blockchain (ordered list of blocks)
    DeadBlock deadBlock;            // Rejected vote tracking system
    
    // Private helper: Gets the most recent block in the chain
    Block getLatestBlock() const;

public:
    // Constructor: Initializes blockchain with genesis block
    Blockchain();
    
    // Adds a new block to the chain (automatically links to previous block)
    void addBlock(Block newBlock);
    
    // Validates and adds a vote to a pending block
    // Returns: true if vote was valid and added, false if rejected
    bool addVoteToPendingBlock(Block& pendingBlock, const Vote& vote);
    
    // Check if a voter has already voted anywhere in the blockchain
    // Time Complexity: O(n*m) where n = blocks, m = avg votes per block
    bool hasVoterVoted(const std::string& voterTempID) const;
    
    // Validates entire blockchain integrity
    // Returns: true if all blocks are valid and properly linked
    bool isChainValid() const;
    
    // Gets the entire chain (read-only)
    const std::vector<Block>& getChain() const;
    
    // Display: Prints entire blockchain with validation status
    void display() const;
    
    // Statistics
    int getChainLength() const;
    int getTotalVotes() const;
    
    // DeadBlock access
    const DeadBlock& getDeadBlock() const;
    void displayDeadBlock() const;
    void displayDeadBlockSummary() const;
};

#endif // BLOCKCHAIN_H