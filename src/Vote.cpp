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
// Validates that vote has valid non-empty fields
bool Vote::isValid() const {
    return validateFields(voterTempID, candidate);
}

// Static validation method - checks vote fields before creating Vote object
// Returns: true if both fields are non-empty and don't contain only whitespace
bool Vote::validateFields(const std::string& voterId, const std::string& candidateName) {
    
// Check for empty strings
if (voterId.empty() || candidateName.empty()) {
return false;
}

 // Check for whitespace-only strings
    bool voterIdValid = false;
    bool candidateValid = false;
    
    for (char c : voterId) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            voterIdValid = true;
            break;
        }
    }
    
    for (char c : candidateName) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            candidateValid = true;
            break;
        }
    }
    
    return voterIdValid && candidateValid;
}