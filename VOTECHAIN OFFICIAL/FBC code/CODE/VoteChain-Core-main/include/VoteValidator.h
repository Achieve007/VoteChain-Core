// include/VoteValidator.h
// Centralized vote validation logic with detailed error reporting
// Provides comprehensive validation for voting system integrity

#ifndef VOTE_VALIDATOR_H
#define VOTE_VALIDATOR_H

#include <string>
#include <vector>

// Validation result structure with detailed error information
struct ValidationResult {
    bool isValid;
    std::string errorMessage;
    
    ValidationResult(bool valid = true, const std::string& error = "")
        : isValid(valid), errorMessage(error) {}
};

class VoteValidator {
public:
    // Validates voter ID format and content
    static ValidationResult validateVoterID(const std::string& voterID);
    
    // Validates candidate name format and content
    static ValidationResult validateCandidate(const std::string& candidate);
    
    // Comprehensive vote validation
    static ValidationResult validateVote(const std::string& voterID, 
                                        const std::string& candidate);
    
    // Constants for validation rules
    static const size_t MIN_VOTER_ID_LENGTH = 3;
    static const size_t MAX_VOTER_ID_LENGTH = 50;
    static const size_t MIN_CANDIDATE_LENGTH = 2;
    static const size_t MAX_CANDIDATE_LENGTH = 100;

private:
    // Helper: Check if string contains only whitespace
    static bool isWhitespaceOnly(const std::string& str);
    
    // Helper: Check for potentially malicious characters
    static bool containsInvalidCharacters(const std::string& str);
};

#endif // VOTE_VALIDATOR_H