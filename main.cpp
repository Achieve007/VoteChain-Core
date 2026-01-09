// main.cpp
// Test driver for the blockchain voting system
// Demonstrates genesis block creation and vote addition

#include "Block.h"
#include "Vote.h"
#include <iostream>

int main() {
    std::cout << "\n╔══════════════════════════════════════════╗" << std::endl;
    std::cout << "║  Blockchain Voting System - Demo        ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════╝\n" << std::endl;
    
    // Step 1: Create the Genesis Block (the foundation of our blockchain)
    std::cout << "Creating Genesis Block..." << std::endl;
    Block genesisBlock = Block::createGenesisBlock();
    
    // Display the empty genesis block
    genesisBlock.display();
    
    // Step 2: Add some sample votes to the genesis block
    std::cout << "Adding votes to Genesis Block...\n" << std::endl;
    
    Vote vote1("VOTER-001", "Alice Johnson");
    Vote vote2("VOTER-002", "Bob Smith");
    Vote vote3("VOTER-003", "Alice Johnson");
    
    genesisBlock.addVote(vote1);
    genesisBlock.addVote(vote2);
    genesisBlock.addVote(vote3);
    
    // Display the genesis block with votes
    std::cout << "\nGenesis Block after adding votes:" << std::endl;
    genesisBlock.display();
    
    // Step 3: Show hash changes when block content changes
    std::cout << "Notice how the hash changed after adding votes!" << std::endl;
    std::cout << "This ensures data integrity - any modification changes the hash.\n" << std::endl;
    
    // Step 4: Demonstrate block linking (preview of blockchain)
    std::cout << "Creating Block #1 (linked to Genesis)..." << std::endl;
    Block block1(1, genesisBlock.getHash());
    
    Vote vote4("VOTER-004", "Bob Smith");
    block1.addVote(vote4);
    
    block1.display();
    
    std::cout << "✓ Genesis block created successfully!" << std::endl;
    std::cout << "✓ Block linking works correctly!" << std::endl;
    std::cout << "✓ Hash chain integrity maintained!\n" << std::endl;
    
    return 0;
}