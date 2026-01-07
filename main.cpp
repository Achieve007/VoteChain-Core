#include "include/Vote.h"
#include "include/Block.h"
#include <iostream>

int main() {
    std::cout << "=================================\n";
    std::cout << "  BLOCKCHAIN VOTING SYSTEM v1.0  \n";
    std::cout << "  Day 1-2: Genesis Block Demo    \n";
    std::cout << "=================================\n\n";
    
    // Create the GENESIS BLOCK (first block in blockchain)
    // Genesis block has index 0 and no previous hash
    Block genesisBlock(0, "0");
    
    std::cout << "✓ Genesis Block Created!\n";
    genesisBlock.display();
    
    std::cout << "\n--- Adding some test votes to Genesis Block ---\n";
    
    // Create and add some sample votes
    Vote vote1("VOTER_001", "Alice");
    Vote vote2("VOTER_002", "Bob");
    Vote vote3("VOTER_003", "Alice");
    
    genesisBlock.addVote(vote1);
    std::cout << "✓ Added vote from VOTER_001\n";
    
    genesisBlock.addVote(vote2);
    std::cout << "✓ Added vote from VOTER_002\n";
    
    genesisBlock.addVote(vote3);
    std::cout << "✓ Added vote from VOTER_003\n";
    
    // Display updated Genesis Block
    std::cout << "\n--- Updated Genesis Block ---\n";
    genesisBlock.display();
    
    std::cout << "\n🎉 Day 1-2 Complete! Genesis Block working!\n";
    std::cout << "Next: Day 3-4 will add SHA-256 hashing and blockchain chain.\n";
    
    return 0;
}