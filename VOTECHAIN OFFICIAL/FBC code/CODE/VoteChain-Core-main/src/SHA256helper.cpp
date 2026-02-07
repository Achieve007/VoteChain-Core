// src/SHA256Helper.cpp
// Implementation of SHA-256 hashing using OpenSSL library

#include "../include/SHA256Helper.h"  // Note: Changed from "SHA256Helper.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

// Computes SHA-256 hash and returns as hex string
std::string SHA256Helper::hash(const std::string& input) {
    // Buffer to store the 256-bit (32-byte) hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // Compute SHA-256 hash
    // SHA256_DIGEST_LENGTH = 32 bytes = 256 bits
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.length());
    SHA256_Final(hash, &sha256);
    
    // Convert binary hash to readable hex string
    return bytesToHex(hash, SHA256_DIGEST_LENGTH);
}

// Converts raw bytes to hexadecimal string representation
// Each byte becomes two hex characters (e.g., 0xFF -> "ff")
std::string SHA256Helper::bytesToHex(const unsigned char* data, size_t length) {
    std::ostringstream oss;
    
    // Set output format to hexadecimal, lowercase, zero-padded
    oss << std::hex << std::setfill('0');
    
    for (size_t i = 0; i < length; ++i) {
        // Convert each byte to 2-digit hex (e.g., 15 -> "0f")
        oss << std::setw(2) << static_cast<int>(data[i]);
    }
    
    return oss.str();
}