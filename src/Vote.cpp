#include "../include/Vote.h"
#include <iostream>
#include <sstream>

// Constructor - initializes vote with ID and candidate
Vote::Vote(const std::string& voterID, const std::string& candidateName) 
    : voterTempID(voterID), candidate(candidateName) {
    // Automatically record current timestamp
    timestamp = time(nullptr);
}

// Getter methods
std::string Vote::getVoterTempID() const {
    return voterTempID;
}

std::string Vote::getCandidate() const {
    return candidate;
}

time_t Vote::getTimestamp() const {
    return timestamp;
}

// Display vote information to console
void Vote::display() const {
    std::cout << "Vote [ID: " << voterTempID 
              << ", Candidate: " << candidate 
              << ", Time: " << ctime(&timestamp) << "]";
}

// Convert vote to string (useful for hashing later)
std::string Vote::toString() const {
    std::ostringstream oss;
    oss << voterTempID << candidate << timestamp;
    return oss.str();
}