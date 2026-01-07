#include "../include/Block.h"
#include <iostream>
#include <sstream>

// Constructor - creates a new block
Block::Block(int idx, const std::string& prevHash) 
    : index(idx), previousHash(prevHash) {
    timestamp = time(nullptr);
    hash = calculateHash();  // Calculate hash when block is created
}

// Add a vote to this block
void Block::addVote(const Vote& vote) {
    votes.push_back(vote);
    // Recalculate hash after adding vote
    hash = calculateHash();
}

// Dummy hash function (Day 1-2) - will be replaced with SHA-256 later
std::string Block::calculateHash() const {
    std::ostringstream oss;
    
    // Combine all block data into one string
    oss << index << previousHash << timestamp;
    
    // Add all votes to the hash calculation
    for (const auto& vote : votes) {
        oss << vote.toString();
    }
    
    // For now, just return a simple "hash" (dummy)
    // We'll replace this with real SHA-256 on Day 3-4
    std::string data = oss.str();
    std::string dummyHash = "HASH_" + std::to_string(data.length()) + "_" + std::to_string(index);
    
    return dummyHash;
}

// Getter methods
int Block::getIndex() const {
    return index;
}

std::string Block::getPreviousHash() const {
    return previousHash;
}

std::string Block::getHash() const {
    return hash;
}

time_t Block::getTimestamp() const {
    return timestamp;
}

const std::vector<Vote>& Block::getVotes() const {
    return votes;
}

// Display block information
void Block::display() const {
    std::cout << "\n========== BLOCK #" << index << " ==========\n";
    std::cout << "Timestamp: " << ctime(&timestamp);
    std::cout << "Previous Hash: " << previousHash << "\n";
    std::cout << "Current Hash: " << hash << "\n";
    std::cout << "Number of Votes: " << votes.size() << "\n";
    
    if (!votes.empty()) {
        std::cout << "Votes in this block:\n";
        for (const auto& vote : votes) {
            std::cout << "  ";
            vote.display();
        }
    }
    std::cout << "================================\n";
}