// src/Vote.cpp
// Implementation of Vote class methods

#include "Vote.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// Constructor with auto timestamp
Vote::Vote(const std::string& voterId, const std::string& candidateName)
    : voterTempID(voterId), candidate(candidateName) {
    // Get current system time
    timestamp = std::time(nullptr);
}

// Constructor with manual timestamp (useful for testing/debugging)
Vote::Vote(const std::string& voterId, const std::string& candidateName, std::time_t voteTime)
    : voterTempID(voterId), candidate(candidateName), timestamp(voteTime) {
}

// Getter implementations
std::string Vote::getVoterTempID() const {
    return voterTempID;
}

std::string Vote::getCandidate() const {
    return candidate;
}

std::time_t Vote::getTimestamp() const {
    return timestamp;
}

// Converts vote to string representation for hashing
// Format: "VoterID|Candidate|Timestamp"
std::string Vote::toString() const {
    std::ostringstream oss;
    oss << voterTempID << "|" << candidate << "|" << timestamp;
    return oss.str();
}

// Pretty-print vote details to console
void Vote::display() const {
    std::cout << "  Vote: " << voterTempID 
              << " -> " << candidate 
              << " (Time: " << timestamp << ")" << std::endl;
}