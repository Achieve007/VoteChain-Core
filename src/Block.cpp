// src/Block.cpp
// Implementation of Block class methods

#include "Block.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// Constructor: Initialize block with index and previous hash, then calculate its hash
Block::Block(int idx, const std::string& prevHash)
    : index(idx), previousHash(prevHash) {
    // Set creation timestamp
    timestamp = std::time(nullptr);
    // Calculate and store this block's hash
    hash = calculateHash();
}

// Add a vote to this block's transaction list
void Block::addVote(const Vote& vote) {
    votes.push_back(vote);
    // Recalculate hash since block content changed
    hash = calculateHash();
}

// Getter implementations
int Block::getIndex() const {
    return index;
}

std::string Block::getPreviousHash() const {
    return previousHash;
}

std::string Block::getHash() const {
    return hash;
}

std::time_t Block::getTimestamp() const {
    return timestamp;
}

const std::vector<Vote>& Block::getVotes() const {
    return votes;
}

// Simple polynomial rolling hash function (placeholder for SHA-256)
// This is deterministic and produces consistent results across platforms
// TODO: Replace with SHA-256 for production use
std::string Block::calculateHash() const {
    // Concatenate all block data into a single string
    std::ostringstream oss;
    oss << index << previousHash << timestamp;
    
    // Include all votes in the hash calculation
    for (const auto& vote : votes) {
        oss << vote.toString();
    }
    
    std::string data = oss.str();
    
    // Simple polynomial rolling hash (base 31)
    unsigned long long hashValue = 0;
    const unsigned long long prime = 31;
    const unsigned long long mod = 1e9 + 9; // Large prime for modulo
    
    for (char c : data) {
        hashValue = (hashValue * prime + static_cast<unsigned long long>(c)) % mod;
    }
    
    // Convert to hex string representation
    std::ostringstream hashStream;
    hashStream << std::hex << std::setw(16) << std::setfill('0') << hashValue;
    return hashStream.str();
}

// Pretty-print block information with all votes
void Block::display() const {
    std::cout << "\n========================================" << std::endl;
    std::cout << "Block #" << index << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Timestamp: " << timestamp << std::endl;
    std::cout << "Previous Hash: " << previousHash << std::endl;
    std::cout << "Hash: " << hash << std::endl;
    std::cout << "Number of Votes: " << votes.size() << std::endl;
    
    if (!votes.empty()) {
        std::cout << "\nVotes in this block:" << std::endl;
        for (const auto& vote : votes) {
            vote.display();
        }
    }
    std::cout << "========================================\n" << std::endl;
}

// Static factory method: Creates the genesis block (first block in chain)
// Genesis block has index 0 and previous hash "0"
Block Block::createGenesisBlock() {
    return Block(0, "0");
}