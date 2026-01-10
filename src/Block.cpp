// src/Block.cpp
// Implementation of Block class methods with SHA-256 hashing

#include "Block.h"
#include "SHA256Helper.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// Constructor: Initialize block with index and previous hash, then calculate SHA-256
Block::Block(int idx, const std::string& prevHash)
    : index(idx), previousHash(prevHash) {
    // Set creation timestamp
    timestamp = std::time(nullptr);
    // Calculate and store this block's SHA-256 hash
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

// SHA-256 hash calculation using all block data
// Any change to block data will result in completely different hash
std::string Block::calculateHash() const {
    // Concatenate all block data into a single string
    std::ostringstream oss;
    oss << index << previousHash << timestamp;
    
    // Include all votes in the hash calculation
    for (const auto& vote : votes) {
        oss << vote.toString();
    }
    
    std::string data = oss.str();
    
    // Compute and return SHA-256 hash
    return SHA256Helper::hash(data);
}

// Validates that the block's stored hash matches its calculated hash
// Returns false if block has been tampered with
bool Block::isValid() const {
    return hash == calculateHash();
}

// Pretty-print block information with all votes
void Block::display() const {
    std::cout << "\n========================================" << std::endl;
    std::cout << "Block #" << index << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Timestamp: " << timestamp << std::endl;
    std::cout << "Previous Hash: " << previousHash.substr(0, 16) << "..." << std::endl;
    std::cout << "Block Hash: " << hash.substr(0, 16) << "..." << std::endl;
    std::cout << "Full Hash: " << hash << std::endl;
    std::cout << "Number of Votes: " << votes.size() << std::endl;
    std::cout << "Valid: " << (isValid() ? "✓ YES" : "✗ NO") << std::endl;
    
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