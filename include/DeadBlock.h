// include/DeadBlock.h
// DeadBlock system for tracking rejected votes
// Provides audit trail and transparency for invalid/duplicate votes

#ifndef DEADBLOCK_H
#define DEADBLOCK_H

#include <string>
#include <vector>
#include <ctime>

// Rejection reasons enumeration for categorization
enum class RejectionReason {
    EMPTY_VOTER_ID,              // Voter ID is empty
    EMPTY_CANDIDATE,             // Candidate name is empty
    WHITESPACE_ONLY,             // Field contains only whitespace
    VOTER_ID_TOO_SHORT,          // Below minimum length
    VOTER_ID_TOO_LONG,           // Exceeds maximum length
    CANDIDATE_TOO_SHORT,         // Below minimum length
    CANDIDATE_TOO_LONG,          // Exceeds maximum length
    INVALID_CHARACTERS,          // Contains forbidden characters
    DUPLICATE_CROSS_CHAIN,       // Voter already voted in blockchain
    DUPLICATE_SAME_BLOCK,        // Voter already in pending block
    UNKNOWN                      // Unspecified reason
};

// Metadata for a single rejected vote
struct RejectedVoteMetadata {
    std::string voterTempID;         // ID of voter who attempted to vote
    std::string candidate;           // Candidate they tried to vote for (if provided)
    std::time_t timestamp;           // When the vote was rejected
    RejectionReason reason;          // Why it was rejected
    std::string detailedMessage;     // Human-readable explanation
    
    // Constructor
    RejectedVoteMetadata(const std::string& voterId, 
                        const std::string& candidateName,
                        RejectionReason rejectionReason,
                        const std::string& message = "");
};

// DeadBlock: Container for rejected votes
class DeadBlock {
private:
    std::vector<RejectedVoteMetadata> invalidVotes;      // Invalid format votes
    std::vector<RejectedVoteMetadata> duplicateVotes;    // Duplicate voter votes
    std::time_t creationTime;                            // When DeadBlock was created
    
public:
    // Constructor: Creates DeadBlock with current timestamp
    DeadBlock();
    
    // Log an invalid vote (format/field validation failure)
    void logInvalidVote(const std::string& voterTempID,
                       const std::string& candidate,
                       RejectionReason reason,
                       const std::string& message = "");
    
    // Log a duplicate vote (already voted in chain or block)
    void logDuplicateVote(const std::string& voterTempID,
                         const std::string& candidate,
                         RejectionReason reason,
                         const std::string& message = "");
    
    // Getters
    const std::vector<RejectedVoteMetadata>& getInvalidVotes() const;
    const std::vector<RejectedVoteMetadata>& getDuplicateVotes() const;
    int getTotalRejected() const;
    int getInvalidCount() const;
    int getDuplicateCount() const;
    std::time_t getCreationTime() const;
    
    // Display methods
    void displayInvalidVotes() const;
    void displayDuplicateVotes() const;
    void displayAll() const;
    void displaySummary() const;
    
    // Export to string (for logging/persistence)
    std::string toCSV() const;
    std::string toJSON() const;
    
    // Helper: Convert RejectionReason to string
    static std::string reasonToString(RejectionReason reason);
};

#endif // DEADBLOCK_H