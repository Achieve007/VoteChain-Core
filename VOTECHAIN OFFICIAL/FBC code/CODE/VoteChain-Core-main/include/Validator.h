// include/Validator.h
// Validator entity for Proof of Authority consensus
// Each validator is a trusted authority who can approve blocks

#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <ctime>

// Validator class: Represents an authorized validator in PoA network
class Validator {
private:
    std::string validatorID;        // Unique identifier (e.g., "VALIDATOR-001")
    std::string name;               // Validator's organization name
    std::string publicKey;          // Simulated public key (in production: real crypto key)
    bool isActive;                  // Whether validator is currently active
    int blocksValidated;            // Statistics: number of blocks validated
    std::time_t registeredTime;     // When validator was registered

public:
    // Constructor
    Validator(const std::string& id, const std::string& validatorName, 
              const std::string& pubKey);
    
    // Getters
    std::string getValidatorID() const;
    std::string getName() const;
    std::string getPublicKey() const;
    bool getIsActive() const;
    int getBlocksValidated() const;
    std::time_t getRegisteredTime() const;
    
    // Setters
    void setActive(bool active);
    void incrementBlocksValidated();
    
    // Generate signature for a block
    // In production: This would use real cryptographic signing
    // For simulation: We create a deterministic signature
    std::string signBlock(const std::string& blockHash) const;
    
    // Verify a signature (simulated)
    static bool verifySignature(const std::string& blockHash,
                               const std::string& signature,
                               const std::string& publicKey);
    
    // Display validator info
    void display() const;
};

// Validator signature structure
struct ValidatorSignature {
    std::string validatorID;        // Who signed
    std::string signature;          // The signature
    std::time_t timestamp;          // When signed
    
    ValidatorSignature(const std::string& id, const std::string& sig);
};

#endif // VALIDATOR_H