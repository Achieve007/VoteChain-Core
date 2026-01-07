#ifndef VOTE_H
#define VOTE_H

#include <string>
#include <ctime>

// Vote class represents a single vote in the system
class Vote {
private:
    std::string voterTempID;  // Temporary anonymous voter ID
    std::string candidate;     // Candidate name
    time_t timestamp;          // When vote was cast

public:
    // Constructor
    Vote(const std::string& voterID, const std::string& candidateName);
    
    // Getters (const methods - they don't modify object)
    std::string getVoterTempID() const;
    std::string getCandidate() const;
    time_t getTimestamp() const;
    
    // Display vote information
    void display() const;
    
    // Convert vote to string format
    std::string toString() const;
};

#endif // VOTE_H