// include/SHA256Helper.h
// Utility class for SHA-256 cryptographic hashing using OpenSSL
// Provides a simple interface to hash strings into secure 256-bit digests

#ifndef SHA256_HELPER_H
#define SHA256_HELPER_H

#include <string>

class SHA256Helper {
public:
    // Computes SHA-256 hash of input string
    // Returns: 64-character hexadecimal string representation
    // Example: "hello" -> "2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824"
    static std::string hash(const std::string& input);
    
private:
    // Helper: Converts byte array to hex string
    static std::string bytesToHex(const unsigned char* data, size_t length);
};

#endif // SHA256_HELPER_H