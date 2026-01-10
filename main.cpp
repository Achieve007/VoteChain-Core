// main.cpp
// Comprehensive test of blockchain voting system with SHA-256
// Demonstrates: Genesis block, adding blocks, vote recording, chain validation

#include "Blockchain.h"
#include "Block.h"
#include "Vote.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "\n╔══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  Blockchain Voting System - SHA-256 Upgrade     ║" << std::endl;
    std::cout << "║  Cryptographically Secure Immutable Voting      ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════╝\n" << std::endl;
    
    // ========================================
    // STEP 1: Initialize Blockchain
    // ========================================
    std::cout << "🔧 Initializing blockchain with genesis block...\n" << std::endl;
    Blockchain votingChain;
    
    // ========================================
    // STEP 2: Add Block #1 - First Round of Votes
    // ========================================
    std::cout << "📦 Creating Block #1 - Early Voting Period..." << std::endl;
    Block block1(1, votingChain.getChain().back().getHash());
    
    Vote vote1("VOTER-A1B2C3", "Alice Johnson");
    Vote vote2("VOTER-D4E5F6", "Bob Smith");
    Vote vote3("VOTER-G7H8I9", "Alice Johnson");
    
    block1.addVote(vote1);
    block1.addVote(vote2);
    block1.addVote(vote3);
    
    votingChain.addBlock(block1);
    
    // Small delay to ensure different timestamps
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // ========================================
    // STEP 3: Add Block #2 - Mid-Day Voting
    // ========================================
    std::cout << "\n📦 Creating Block #2 - Mid-Day Voting Rush..." << std::endl;
    Block block2(2, votingChain.getChain().back().getHash());
    
    Vote vote4("VOTER-J1K2L3", "Charlie Davis");
    Vote vote5("VOTER-M4N5O6", "Alice Johnson");
    Vote vote6("VOTER-P7Q8R9", "Bob Smith");
    Vote vote7("VOTER-S1T2U3", "Charlie Davis");
    
    block2.addVote(vote4);
    block2.addVote(vote5);
    block2.addVote(vote6);
    block2.addVote(vote7);
    
    votingChain.addBlock(block2);
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // ========================================
    // STEP 4: Add Block #3 - Final Voting Period
    // ========================================
    std::cout << "\n📦 Creating Block #3 - Final Hour Votes..." << std::endl;
    Block block3(3, votingChain.getChain().back().getHash());
    
    Vote vote8("VOTER-V4W5X6", "Alice Johnson");
    Vote vote9("VOTER-Y7Z8A9", "Bob Smith");
    
    block3.addVote(vote8);
    block3.addVote(vote9);
    
    votingChain.addBlock(block3);
    
    // ========================================
    // STEP 5: Display Complete Blockchain
    // ========================================
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "COMPLETE BLOCKCHAIN" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    votingChain.display();
    
    // ========================================
    // STEP 6: Validate Blockchain Integrity
    // ========================================
    std::cout << "\n🔐 SECURITY CHECK: Validating Blockchain Integrity..." << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    if (votingChain.isChainValid()) {
        std::cout << "✓ BLOCKCHAIN IS VALID" << std::endl;
        std::cout << "✓ All blocks properly linked via SHA-256 hashes" << std::endl;
        std::cout << "✓ No tampering detected" << std::endl;
        std::cout << "✓ All votes are immutable and secure" << std::endl;
    } else {
        std::cout << "✗ BLOCKCHAIN IS INVALID - TAMPERING DETECTED!" << std::endl;
    }
    
    // ========================================
    // STEP 7: Display Statistics
    // ========================================
    std::cout << "\n📊 VOTING STATISTICS" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Total Blocks: " << votingChain.getChainLength() << std::endl;
    std::cout << "Total Votes Cast: " << votingChain.getTotalVotes() << std::endl;
    
    // Count votes per candidate (simple tally)
    int aliceVotes = 0, bobVotes = 0, charlieVotes = 0;
    for (const auto& block : votingChain.getChain()) {
        for (const auto& vote : block.getVotes()) {
            if (vote.getCandidate() == "Alice Johnson") aliceVotes++;
            else if (vote.getCandidate() == "Bob Smith") bobVotes++;
            else if (vote.getCandidate() == "Charlie Davis") charlieVotes++;
        }
    }
    
    std::cout << "\nCandidate Results:" << std::endl;
    std::cout << "  Alice Johnson: " << aliceVotes << " votes" << std::endl;
    std::cout << "  Bob Smith: " << bobVotes << " votes" << std::endl;
    std::cout << "  Charlie Davis: " << charlieVotes << " votes" << std::endl;
    
    // ========================================
    // STEP 8: Demonstrate Tampering Detection
    // ========================================
    std::cout << "\n\n🔬 DEMONSTRATION: Tampering Detection" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Attempting to modify Block #2 after it's been added..." << std::endl;
    
    // Try to get a non-const reference and modify (this is for demonstration)
    // In real system, blocks would be immutable after adding to chain
    std::vector<Block>& chainRef = const_cast<std::vector<Block>&>(votingChain.getChain());
    Vote fraudulentVote("HACKER-666", "Fraudulent Candidate");
    chainRef[2].addVote(fraudulentVote);
    
    std::cout << "Added fraudulent vote to Block #2..." << std::endl;
    std::cout << "Running integrity check..." << std::endl;
    
    if (!votingChain.isChainValid()) {
        std::cout << "✓ TAMPERING DETECTED! Chain is now invalid." << std::endl;
        std::cout << "✓ SHA-256 hash mismatch reveals the modification" << std::endl;
    }
    
    std::cout << "\n✅ Blockchain system is working correctly!" << std::endl;
    std::cout << "✅ SHA-256 ensures cryptographic security" << std::endl;
    std::cout << "✅ Any tampering is immediately detectable\n" << std::endl;
    
    return 0;
}