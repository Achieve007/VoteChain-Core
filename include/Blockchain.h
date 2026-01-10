// include/Blockchain.h
// Manages the entire blockchain: creates, validates, and maintains the chain
// Ensures immutability and cryptographic integrity of the voting system

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include <vector>

class Blockchain {
private:
    std::vector<Block> chain;       // The complete blockchain (ordered list of blocks)
    
    // Private helper: Gets the most recent block in the chain
    Block getLatestBlock() const;

public:
    // Constructor: Initializes blockchain with genesis block
    Blockchain();
    
    // Adds a new block to the chain (automatically links to previous block)
    void addBlock(Block newBlock);
    
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
};

#endif // BLOCKCHAIN_H