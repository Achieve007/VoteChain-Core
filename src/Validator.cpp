// src/Validator.cpp
// Implementation of Validator class for PoA consensus

#include "Validator.h"
#include "SHA256Helper.h"
#include <iostream>
#include <sstream>

// Constructor
Validator::Validator(const std::string& id, const std::string& validatorName,
                    const std::string& pubKey)
    : validatorID(id), name(validatorName), publicKey(pubKey),
      isActive(true), blocksValidated(0) {
    registeredTime = std::time(nullptr);
}

// Getters
std::string Validator::getValidatorID() const {
    return validatorID;
}

std::string Validator::getName() const {
    return name;
}

std::string Validator::getPublicKey() const {
    return publicKey;
}

bool Validator::getIsActive() const {
    return isActive;
}

int Validator::getBlocksValidated() const {
    return blocksValidated;
}

std::time_t Validator::getRegisteredTime() const {
    return registeredTime;
}

// Setters
void Validator::setActive(bool active) {
    isActive = active;
}

void Validator::incrementBlocksValidated() {
    blocksValidated++;
}

// Sign a block (simulated digital signature)
// In production: Use ECDSA or similar cryptographic signing
// For simulation: SHA256(blockHash + validatorID + publicKey)
std::string Validator::signBlock(const std::string& blockHash) const {
    if (!isActive) {
        return "";  // Inactive validators cannot sign
    }
    
    // Create signature by hashing: blockHash + validatorID + publicKey
    std::string signatureData = blockHash + validatorID + publicKey;
    return SHA256Helper::hash(signatureData);
}

// Verify a signature (simulated)
// In production: Use public key cryptography to verify
bool Validator::verifySignature(const std::string& blockHash,
                               const std::string& signature,
                               const std::string& publicKey) {
    // For simulation: We can't reverse the hash, but we can check format
    // In real implementation: Use ECDSA verify with public key
    
    // Basic validation: signature should be 64 hex characters (SHA256)
    if (signature.length() != 64) {
        return false;
    }
    
    // Check if signature contains only hex characters
    for (char c : signature) {
        if (!std::isxdigit(c)) {
            return false;
        }
    }
    
    // In our simulation, we assume if format is correct, signature is valid
    // Real implementation would use: ECDSA_verify(hash, signature, publicKey)
    return true;
}

// Display validator information
void Validator::display() const {
    std::cout << "  Validator: " << validatorID << " (" << name << ")" << std::endl;
    std::cout << "    Status: " << (isActive ? "ACTIVE" : "INACTIVE") << std::endl;
    std::cout << "    Public Key: " << publicKey.substr(0, 16) << "..." << std::endl;
    std::cout << "    Blocks Validated: " << blocksValidated << std::endl;
    std::cout << "    Registered: " << registeredTime << std::endl;
}

// ValidatorSignature constructor
ValidatorSignature::ValidatorSignature(const std::string& id, const std::string& sig)
    : validatorID(id), signature(sig) {
    timestamp = std::time(nullptr);
}