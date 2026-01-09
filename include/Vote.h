// include/Vote.h
// Represents a single vote in the blockchain voting system
// Each vote is immutable once created and contains voter ID, candidate, and timestamp

#ifndef VOTE_H
#define VOTE_H

#include <string>
#include <ctime>

// Vote class represents a single vote in the system
class Vote {
private:
    std::string voterTempID;    // Temporary anonymous voter identifier
    std::string candidate;      // Candidate name or ID
    std::time_t timestamp;      // Unix timestamp of when vote was cast

public:
    // Constructor: Creates a new vote with current timestamp
    Vote(const std::string& voterId, const std::string& candidateName);
    
    // Constructor: Creates a vote with specific timestamp (useful for testing)
    Vote(const std::string& voterId, const std::string& candidateName, std::time_t voteTime);
    
    // Getters: Provide read-only access to vote data
    std::string getVoterTempID() const;
    std::string getCandidate() const;
    std::time_t getTimestamp() const;
    
    // Serialization: Converts vote to string format for hashing
    std::string toString() const;
    
    // Display: Pretty-prints vote information
    void display() const;
};

#endif // VOTE_H