// src/DeadBlock.cpp
// Implementation of DeadBlock system for rejected vote tracking

#include "DeadBlock.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// RejectedVoteMetadata constructor
RejectedVoteMetadata::RejectedVoteMetadata(const std::string& voterId,
                                           const std::string& candidateName,
                                           RejectionReason rejectionReason,
                                           const std::string& message): voterTempID(voterId), candidate(candidateName), 
      reason(rejectionReason), detailedMessage(message) {
    timestamp = std::time(nullptr);
}

// DeadBlock constructor
DeadBlock::DeadBlock() {
    creationTime = std::time(nullptr);
}

// Log an invalid vote (format/validation failure)
void DeadBlock::logInvalidVote(const std::string& voterTempID,
                               const std::string& candidate,
                               RejectionReason reason,
                               const std::string& message) {
    RejectedVoteMetadata metadata(voterTempID, candidate, reason, message);
    invalidVotes.push_back(metadata);
    
    // Console logging for immediate feedback
    std::cout << "⚠️  INVALID VOTE LOGGED: " << voterTempID 
              << " - " << reasonToString(reason) << std::endl;
}

// Log a duplicate vote
void DeadBlock::logDuplicateVote(const std::string& voterTempID,
                                 const std::string& candidate,
                                 RejectionReason reason,
                                 const std::string& message) {
    RejectedVoteMetadata metadata(voterTempID, candidate, reason, message);
    duplicateVotes.push_back(metadata);
    
    // Console logging for immediate feedback
    std::cout << "🔁 DUPLICATE VOTE LOGGED: " << voterTempID 
              << " - " << reasonToString(reason) << std::endl;
}

// Getters
const std::vector<RejectedVoteMetadata>& DeadBlock::getInvalidVotes() const {
    return invalidVotes;
}

const std::vector<RejectedVoteMetadata>& DeadBlock::getDuplicateVotes() const {
    return duplicateVotes;
}

int DeadBlock::getTotalRejected() const {
    return static_cast<int>(invalidVotes.size() + duplicateVotes.size());
}

int DeadBlock::getInvalidCount() const {
    return static_cast<int>(invalidVotes.size());
}

int DeadBlock::getDuplicateCount() const {
    return static_cast<int>(duplicateVotes.size());
}

std::time_t DeadBlock::getCreationTime() const {
    return creationTime;
}

// Display invalid votes
void DeadBlock::displayInvalidVotes() const {
    if (invalidVotes.empty()) {
        std::cout << "  No invalid votes logged." << std::endl;
        return;
    }
    
    std::cout << "\n  INVALID VOTES (" << invalidVotes.size() << "):" << std::endl;
    std::cout << "  " << std::string(70, '-') << std::endl;
    
    for (size_t i = 0; i < invalidVotes.size(); ++i) {
        const auto& vote = invalidVotes[i];
        std::cout << "  [" << (i + 1) << "] Voter: " << vote.voterTempID 
                  << " | Candidate: " << (vote.candidate.empty() ? "(none)" : vote.candidate)
                  << std::endl;
        std::cout << "      Reason: " << reasonToString(vote.reason) << std::endl;
        if (!vote.detailedMessage.empty()) {
            std::cout << "      Details: " << vote.detailedMessage << std::endl;
        }
        std::cout << "      Time: " << vote.timestamp << std::endl;
    }
}

// Display duplicate votes
void DeadBlock::displayDuplicateVotes() const {
    if (duplicateVotes.empty()) {
        std::cout << "  No duplicate votes logged." << std::endl;
        return;
    }
    
    std::cout << "\n  DUPLICATE VOTES (" << duplicateVotes.size() << "):" << std::endl;
    std::cout << "  " << std::string(70, '-') << std::endl;
    
    for (size_t i = 0; i < duplicateVotes.size(); ++i) {
        const auto& vote = duplicateVotes[i];
        std::cout << "  [" << (i + 1) << "] Voter: " << vote.voterTempID 
                  << " | Candidate: " << vote.candidate << std::endl;
        std::cout << "      Reason: " << reasonToString(vote.reason) << std::endl;
        if (!vote.detailedMessage.empty()) {
            std::cout << "      Details: " << vote.detailedMessage << std::endl;
        }
        std::cout << "      Time: " << vote.timestamp << std::endl;
    }
}

// Display all rejected votes
void DeadBlock::displayAll() const {
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              DEADBLOCK - REJECTED VOTES                ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "Created: " << creationTime << std::endl;
    std::cout << "Total Rejected: " << getTotalRejected() 
              << " (Invalid: " << getInvalidCount() 
              << ", Duplicate: " << getDuplicateCount() << ")" << std::endl;
    
    displayInvalidVotes();
    displayDuplicateVotes();
    
    std::cout << "\n" << std::string(60, '=') << "\n" << std::endl;
}

// Display summary statistics
void DeadBlock::displaySummary() const {
    std::cout << "\n📊 DEADBLOCK SUMMARY" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Total Rejected Votes: " << getTotalRejected() << std::endl;
    std::cout << "  - Invalid Format: " << getInvalidCount() << std::endl;
    std::cout << "  - Duplicates: " << getDuplicateCount() << std::endl;
    
    // Breakdown by reason
    if (!invalidVotes.empty() || !duplicateVotes.empty()) {
        std::cout << "\nBreakdown by Rejection Reason:" << std::endl;
        
        // Count occurrences of each reason
        int counts[12] = {0}; // Array for all RejectionReason enum values
        
        for (const auto& vote : invalidVotes) {
            counts[static_cast<int>(vote.reason)]++;
        }
        for (const auto& vote : duplicateVotes) {
            counts[static_cast<int>(vote.reason)]++;
        }
        
        // Display non-zero counts
        for (int i = 0; i < 12; ++i) {
            if (counts[i] > 0) {
                RejectionReason reason = static_cast<RejectionReason>(i);
                std::cout << "  - " << reasonToString(reason) 
                         << ": " << counts[i] << std::endl;
            }
        }
    }
    std::cout << std::string(50, '-') << std::endl;
}

// Export to CSV format
std::string DeadBlock::toCSV() const {
    std::ostringstream oss;
    
    // CSV Header
    oss << "Type,VoterID,Candidate,Reason,Message,Timestamp\n";
    
    // Invalid votes
    for (const auto& vote : invalidVotes) {
        oss << "INVALID,"
            << vote.voterTempID << ","
            << vote.candidate << ","
            << reasonToString(vote.reason) << ","
            << vote.detailedMessage << ","
            << vote.timestamp << "\n";
    }
    
    // Duplicate votes
    for (const auto& vote : duplicateVotes) {
        oss << "DUPLICATE,"
            << vote.voterTempID << ","
            << vote.candidate << ","
            << reasonToString(vote.reason) << ","
            << vote.detailedMessage << ","
            << vote.timestamp << "\n";
    }
    
    return oss.str();
}

// Export to JSON format
std::string DeadBlock::toJSON() const {
    std::ostringstream oss;
    
    oss << "{\n";
    oss << "  \"creationTime\": " << creationTime << ",\n";
    oss << "  \"totalRejected\": " << getTotalRejected() << ",\n";
    oss << "  \"invalidCount\": " << getInvalidCount() << ",\n";
    oss << "  \"duplicateCount\": " << getDuplicateCount() << ",\n";
    
    // Invalid votes array
    oss << "  \"invalidVotes\": [\n";
    for (size_t i = 0; i < invalidVotes.size(); ++i) {
        const auto& vote = invalidVotes[i];
        oss << "    {\n";
        oss << "      \"voterTempID\": \"" << vote.voterTempID << "\",\n";
        oss << "      \"candidate\": \"" << vote.candidate << "\",\n";
        oss << "      \"reason\": \"" << reasonToString(vote.reason) << "\",\n";
        oss << "      \"message\": \"" << vote.detailedMessage << "\",\n";
        oss << "      \"timestamp\": " << vote.timestamp << "\n";
        oss << "    }" << (i < invalidVotes.size() - 1 ? "," : "") << "\n";
    }
    oss << "  ],\n";
    
    // Duplicate votes array
    oss << "  \"duplicateVotes\": [\n";
    for (size_t i = 0; i < duplicateVotes.size(); ++i) {
        const auto& vote = duplicateVotes[i];
        oss << "    {\n";
        oss << "      \"voterTempID\": \"" << vote.voterTempID << "\",\n";
        oss << "      \"candidate\": \"" << vote.candidate << "\",\n";
        oss << "      \"reason\": \"" << reasonToString(vote.reason) << "\",\n";
        oss << "      \"message\": \"" << vote.detailedMessage << "\",\n";
        oss << "      \"timestamp\": " << vote.timestamp << "\n";
        oss << "    }" << (i < duplicateVotes.size() - 1 ? "," : "") << "\n";
    }
    oss << "  ]\n";
    oss << "}\n";
    
    return oss.str();
}

// Helper: Convert RejectionReason enum to string
std::string DeadBlock::reasonToString(RejectionReason reason) {
    switch (reason) {
        case RejectionReason::EMPTY_VOTER_ID:
            return "Empty Voter ID";
        case RejectionReason::EMPTY_CANDIDATE:
            return "Empty Candidate";
        case RejectionReason::WHITESPACE_ONLY:
            return "Whitespace Only";
        case RejectionReason::VOTER_ID_TOO_SHORT:
            return "Voter ID Too Short";
        case RejectionReason::VOTER_ID_TOO_LONG:
            return "Voter ID Too Long";
        case RejectionReason::CANDIDATE_TOO_SHORT:
            return "Candidate Too Short";
        case RejectionReason::CANDIDATE_TOO_LONG:
            return "Candidate Too Long";
        case RejectionReason::INVALID_CHARACTERS:
            return "Invalid Characters";
        case RejectionReason::DUPLICATE_CROSS_CHAIN:
            return "Duplicate (Cross-Chain)";
        case RejectionReason::DUPLICATE_SAME_BLOCK:
            return "Duplicate (Same Block)";
        case RejectionReason::UNKNOWN:
        default:
            return "Unknown";
    }
}