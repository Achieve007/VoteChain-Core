// include/ConsensusPoA.h
// Proof of Authority consensus mechanism
// Implements validator-based block finalization with multi-signature approval

#ifndef CONSENSUS_POA_H
#define CONSENSUS_POA_H

#include "Validator.h"
#include "Block.h"
#include <vector>
#include <map>
#include <string>

// Consensus result enumeration
enum class ConsensusResult {
    APPROVED,           // Block approved by sufficient validators
    REJECTED,           // Block rejected (insufficient signatures)
    PENDING,            // Waiting for more signatures
    INVALID             // Block data is invalid
};

// Pending block awaiting consensus
struct PendingBlock {
    Block block;                                    // The block awaiting approval
    std::vector<ValidatorSignature> signatures;     // Collected signatures
    std::time_t submittedTime;                      // When block was submitted
    bool isFinalized;                               // Whether consensus reached
    
    PendingBlock(const Block& b);
};

// Proof of Authority Consensus Engine
class ConsensusPoA {
private:
    std::vector<Validator> validators;              // List of authorized validators
    int minimumApprovals;                           // Required signatures (e.g., 3 out of 4)
    std::map<std::string, PendingBlock> pendingBlocks;  // Blocks awaiting consensus
    
    // Statistics
    int totalBlocksApproved;
    int totalBlocksRejected;

public:
    // Constructor
    ConsensusPoA(int minApprovals = 3);
    
    // Validator management
    void registerValidator(const Validator& validator);
    bool removeValidator(const std::string& validatorID);
    Validator* getValidator(const std::string& validatorID);
    const std::vector<Validator>& getValidators() const;
    int getActiveValidatorCount() const;
    
    // Block submission and consensus
    bool submitBlockForConsensus(const Block& block);
    ConsensusResult addValidatorSignature(const std::string& blockHash,
                                         const std::string& validatorID);
    bool finalizeBlock(const std::string& blockHash);
    ConsensusResult checkConsensusStatus(const std::string& blockHash) const;
    
    // Validation
    bool hasReachedConsensus(const std::string& blockHash) const;
    bool isBlockFinalized(const std::string& blockHash) const;
    int getSignatureCount(const std::string& blockHash) const;
    
    // Getters
    PendingBlock* getPendingBlock(const std::string& blockHash);
    int getMinimumApprovals() const;
    int getTotalBlocksApproved() const;
    int getTotalBlocksRejected() const;
    
    // Display
    void displayValidators() const;
    void displayPendingBlocks() const;
    void displayConsensusStats() const;
    
    // Helper: Convert ConsensusResult to string
    static std::string consensusResultToString(ConsensusResult result);
};

#endif // CONSENSUS_POA_H