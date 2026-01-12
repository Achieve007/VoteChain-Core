// src/ConsensusPoA.cpp
// Implementation of Proof of Authority consensus mechanism

#include "ConsensusPoA.h"
#include <iostream>
#include <algorithm>

// PendingBlock constructor
PendingBlock::PendingBlock(const Block& b) 
    : block(b), isFinalized(false) {
    submittedTime = std::time(nullptr);
}

// ConsensusPoA constructor
ConsensusPoA::ConsensusPoA(int minApprovals)
    : minimumApprovals(minApprovals), totalBlocksApproved(0), totalBlocksRejected(0) {
}

// Register a new validator
void ConsensusPoA::registerValidator(const Validator& validator) {
    validators.push_back(validator);
    std::cout << "✓ Validator registered: " << validator.getValidatorID() 
              << " (" << validator.getName() << ")" << std::endl;
}

// Remove a validator
bool ConsensusPoA::removeValidator(const std::string& validatorID) {
    auto it = std::find_if(validators.begin(), validators.end(),
        [&validatorID](const Validator& v) { return v.getValidatorID() == validatorID; });
    
    if (it != validators.end()) {
        validators.erase(it);
        std::cout << "✓ Validator removed: " << validatorID << std::endl;
        return true;
    }
    return false;
}

// Get validator by ID
Validator* ConsensusPoA::getValidator(const std::string& validatorID) {
    for (auto& validator : validators) {
        if (validator.getValidatorID() == validatorID) {
            return &validator;
        }
    }
    return nullptr;
}

// Get all validators
const std::vector<Validator>& ConsensusPoA::getValidators() const {
    return validators;
}

// Count active validators
int ConsensusPoA::getActiveValidatorCount() const {
    int count = 0;
    for (const auto& validator : validators) {
        if (validator.getIsActive()) {
            count++;
        }
    }
    return count;
}

// Submit block for consensus voting
bool ConsensusPoA::submitBlockForConsensus(const Block& block) {
    std::string blockHash = block.getHash();
    
    // Check if block already exists
    if (pendingBlocks.find(blockHash) != pendingBlocks.end()) {
        std::cerr << "✗ Block already submitted for consensus" << std::endl;
        return false;
    }
    
    // Validate block first
    if (!block.isValid()) {
        std::cerr << "✗ Cannot submit invalid block for consensus" << std::endl;
        return false;
    }
    
// Add to pending blocks using emplace to avoid default constructor
pendingBlocks.emplace(blockHash, PendingBlock(block));
    
    std::cout << "📋 Block submitted for consensus: " << blockHash.substr(0, 16) 
              << "..." << std::endl;
    std::cout << "   Requires " << minimumApprovals << " out of " 
              << getActiveValidatorCount() << " validator approvals" << std::endl;
    
    return true;
}

// Add validator signature to a pending block
ConsensusResult ConsensusPoA::addValidatorSignature(const std::string& blockHash,
                                                    const std::string& validatorID) {
    // Check if block exists
    auto it = pendingBlocks.find(blockHash);
    if (it == pendingBlocks.end()) {
        std::cerr << "✗ Block not found in pending blocks" << std::endl;
        return ConsensusResult::INVALID;
    }
    
    PendingBlock& pending = it->second;
    
    // Check if already finalized
    if (pending.isFinalized) {
        std::cout << "ℹ️  Block already finalized" << std::endl;
        return ConsensusResult::APPROVED;
    }
    
    // Get validator
    Validator* validator = getValidator(validatorID);
    if (!validator) {
        std::cerr << "✗ Validator not found: " << validatorID << std::endl;
        return ConsensusResult::INVALID;
    }
    
    // Check if validator is active
    if (!validator->getIsActive()) {
        std::cerr << "✗ Validator is inactive: " << validatorID << std::endl;
        return ConsensusResult::INVALID;
    }
    
    // Check if validator already signed
    for (const auto& sig : pending.signatures) {
        if (sig.validatorID == validatorID) {
            std::cout << "ℹ️  Validator already signed this block: " << validatorID << std::endl;
            return checkConsensusStatus(blockHash);
        }
    }
    
    // Generate signature
    std::string signature = validator->signBlock(blockHash);
    if (signature.empty()) {
        std::cerr << "✗ Failed to generate signature" << std::endl;
        return ConsensusResult::INVALID;
    }
    
    // Verify signature
    if (!Validator::verifySignature(blockHash, signature, validator->getPublicKey())) {
        std::cerr << "✗ Signature verification failed" << std::endl;
        return ConsensusResult::INVALID;
    }
    
    // Add signature
    pending.signatures.push_back(ValidatorSignature(validatorID, signature));
    
    std::cout << "✓ Signature added: " << validatorID << " (" 
              << pending.signatures.size() << "/" << minimumApprovals << ")" << std::endl;
    
    // Check if consensus reached
    if (static_cast<int>(pending.signatures.size()) >= minimumApprovals) {
        return ConsensusResult::APPROVED;
    }
    
    return ConsensusResult::PENDING;
}

// Finalize block after consensus reached
bool ConsensusPoA::finalizeBlock(const std::string& blockHash) {
    auto it = pendingBlocks.find(blockHash);
    if (it == pendingBlocks.end()) {
        std::cerr << "✗ Block not found" << std::endl;
        return false;
    }
    
    PendingBlock& pending = it->second;
    
    // Check if already finalized
    if (pending.isFinalized) {
        std::cout << "ℹ️  Block already finalized" << std::endl;
        return true;
    }
    
    // Check if consensus reached
    if (static_cast<int>(pending.signatures.size()) < minimumApprovals) {
        std::cerr << "✗ Insufficient signatures for finalization: " 
                  << pending.signatures.size() << "/" << minimumApprovals << std::endl;
        totalBlocksRejected++;
        return false;
    }
    
    // Finalize block
    pending.isFinalized = true;
    totalBlocksApproved++;
    
    // Update validator statistics
    for (const auto& sig : pending.signatures) {
        Validator* validator = getValidator(sig.validatorID);
        if (validator) {
            validator->incrementBlocksValidated();
        }
    }
    
    std::cout << "✅ BLOCK FINALIZED with " << pending.signatures.size() 
              << " signatures!" << std::endl;
    std::cout << "   Block Hash: " << blockHash.substr(0, 32) << "..." << std::endl;
    
    return true;
}

// Check consensus status of a block
ConsensusResult ConsensusPoA::checkConsensusStatus(const std::string& blockHash) const {
    auto it = pendingBlocks.find(blockHash);
    if (it == pendingBlocks.end()) {
        return ConsensusResult::INVALID;
    }
    
    const PendingBlock& pending = it->second;
    
    if (pending.isFinalized) {
        return ConsensusResult::APPROVED;
    }
    
    if (static_cast<int>(pending.signatures.size()) >= minimumApprovals) {
        return ConsensusResult::APPROVED;
    }
    
    if (pending.signatures.size() > 0) {
        return ConsensusResult::PENDING;
    }
    
    return ConsensusResult::PENDING;
}

// Check if block has reached consensus
bool ConsensusPoA::hasReachedConsensus(const std::string& blockHash) const {
    return checkConsensusStatus(blockHash) == ConsensusResult::APPROVED;
}

// Check if block is finalized
bool ConsensusPoA::isBlockFinalized(const std::string& blockHash) const {
    auto it = pendingBlocks.find(blockHash);
    if (it == pendingBlocks.end()) {
        return false;
    }
    return it->second.isFinalized;
}

// Get signature count for a block
int ConsensusPoA::getSignatureCount(const std::string& blockHash) const {
    auto it = pendingBlocks.find(blockHash);
    if (it == pendingBlocks.end()) {
        return 0;
    }
    return static_cast<int>(it->second.signatures.size());
}

// Get pending block
PendingBlock* ConsensusPoA::getPendingBlock(const std::string& blockHash) {
    auto it = pendingBlocks.find(blockHash);
    if (it == pendingBlocks.end()) {
        return nullptr;
    }
    return &(it->second);
}

// Getters
int ConsensusPoA::getMinimumApprovals() const {
    return minimumApprovals;
}

int ConsensusPoA::getTotalBlocksApproved() const {
    return totalBlocksApproved;
}

int ConsensusPoA::getTotalBlocksRejected() const {
    return totalBlocksRejected;
}

// Display all validators
void ConsensusPoA::displayValidators() const {
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              REGISTERED VALIDATORS                     ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "Total Validators: " << validators.size() << std::endl;
    std::cout << "Active Validators: " << getActiveValidatorCount() << std::endl;
    std::cout << "Minimum Approvals Required: " << minimumApprovals << std::endl;
    std::cout << std::endl;
    
    for (const auto& validator : validators) {
        validator.display();
        std::cout << std::endl;
    }
}

// Display pending blocks
void ConsensusPoA::displayPendingBlocks() const {
    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              PENDING BLOCKS (CONSENSUS)                ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    
    if (pendingBlocks.empty()) {
        std::cout << "No pending blocks." << std::endl;
        return;
    }
    
    for (const auto& pair : pendingBlocks) {
        const PendingBlock& pending = pair.second;
        
        std::cout << "\nBlock #" << pending.block.getIndex() << std::endl;
        std::cout << "  Hash: " << pair.first.substr(0, 32) << "..." << std::endl;
        std::cout << "  Status: " << (pending.isFinalized ? "FINALIZED ✅" : "PENDING ⏳") 
                  << std::endl;
        std::cout << "  Signatures: " << pending.signatures.size() << "/" 
                  << minimumApprovals << std::endl;
        
        if (!pending.signatures.empty()) {
            std::cout << "  Validators who signed:" << std::endl;
            for (const auto& sig : pending.signatures) {
                std::cout << "    - " << sig.validatorID 
                         << " (Time: " << sig.timestamp << ")" << std::endl;
            }
        }
    }
}

// Display consensus statistics
void ConsensusPoA::displayConsensusStats() const {
    std::cout << "\n📊 CONSENSUS STATISTICS" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Total Blocks Approved: " << totalBlocksApproved << std::endl;
    std::cout << "Total Blocks Rejected: " << totalBlocksRejected << std::endl;
    std::cout << "Pending Blocks: " << pendingBlocks.size() << std::endl;
    std::cout << "Active Validators: " << getActiveValidatorCount() << "/" 
              << validators.size() << std::endl;
    std::cout << std::string(50, '-') << std::endl;
}

// Convert ConsensusResult to string
std::string ConsensusPoA::consensusResultToString(ConsensusResult result) {
    switch (result) {
        case ConsensusResult::APPROVED:
            return "APPROVED";
        case ConsensusResult::REJECTED:
            return "REJECTED";
        case ConsensusResult::PENDING:
            return "PENDING";
        case ConsensusResult::INVALID:
            return "INVALID";
        default:
            return "UNKNOWN";
    }
}