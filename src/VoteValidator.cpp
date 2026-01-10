// src/VoteValidator.cpp
// Implementation of comprehensive vote validation logic

#include "VoteValidator.h"
#include <cctype>

// Validates voter ID according to system rules
ValidationResult VoteValidator::validateVoterID(const std::string& voterID) {
    // Check for empty or whitespace-only
    if (voterID.empty()) {
        return ValidationResult(false, "Voter ID cannot be empty");
    }
    
    if (isWhitespaceOnly(voterID)) {
        return ValidationResult(false, "Voter ID cannot contain only whitespace");
    }
    
    // Check length constraints
    if (voterID.length() < MIN_VOTER_ID_LENGTH) {
        return ValidationResult(false, "Voter ID too short (minimum " + 
                               std::to_string(MIN_VOTER_ID_LENGTH) + " characters)");
    }
    
    if (voterID.length() > MAX_VOTER_ID_LENGTH) {
        return ValidationResult(false, "Voter ID too long (maximum " + 
                               std::to_string(MAX_VOTER_ID_LENGTH) + " characters)");
    }
    
    // Check for invalid characters (basic security check)
    if (containsInvalidCharacters(voterID)) {
        return ValidationResult(false, "Voter ID contains invalid characters");
    }
    
    return ValidationResult(true);
}

// Validates candidate name according to system rules
ValidationResult VoteValidator::validateCandidate(const std::string& candidate) {
    // Check for empty or whitespace-only
    if (candidate.empty()) {
        return ValidationResult(false, "Candidate name cannot be empty");
    }
    
    if (isWhitespaceOnly(candidate)) {
        return ValidationResult(false, "Candidate name cannot contain only whitespace");
    }
    
    // Check length constraints
    if (candidate.length() < MIN_CANDIDATE_LENGTH) {
        return ValidationResult(false, "Candidate name too short (minimum " + 
                               std::to_string(MIN_CANDIDATE_LENGTH) + " characters)");
    }
    
    if (candidate.length() > MAX_CANDIDATE_LENGTH) {
        return ValidationResult(false, "Candidate name too long (maximum " + 
                               std::to_string(MAX_CANDIDATE_LENGTH) + " characters)");
    }
    
    return ValidationResult(true);
}

// Comprehensive validation of both voter ID and candidate
ValidationResult VoteValidator::validateVote(const std::string& voterID, 
                                             const std::string& candidate) {
    // Validate voter ID first
    ValidationResult voterResult = validateVoterID(voterID);
    if (!voterResult.isValid) {
        return voterResult;
    }
    
    // Then validate candidate
    ValidationResult candidateResult = validateCandidate(candidate);
    if (!candidateResult.isValid) {
        return candidateResult;
    }
    
    return ValidationResult(true);
}

// Helper: Checks if string is only whitespace
bool VoteValidator::isWhitespaceOnly(const std::string& str) {
    for (char c : str) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

// Helper: Basic check for potentially malicious characters
// In production, this would be more sophisticated
bool VoteValidator::containsInvalidCharacters(const std::string& str) {
    for (char c : str) {
        // Allow alphanumeric, hyphen, underscore, space
        if (!std::isalnum(static_cast<unsigned char>(c)) && 
            c != '-' && c != '_' && c != ' ') {
            return true;
        }
    }
    return false;
}