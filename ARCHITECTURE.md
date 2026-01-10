# 🏗️ Architecture Documentation

## System Overview

The Blockchain Voting System is a secure, immutable voting platform built on blockchain principles. It ensures vote integrity through cryptographic hashing, prevents double-voting through comprehensive validation, and maintains a tamper-proof audit trail.

## Core Components

### 1. Vote Class (`Vote.h`, `Vote.cpp`)

**Purpose**: Represents a single immutable vote record.

**Responsibilities**:
- Store voter temporary ID (anonymous identifier)
- Store candidate selection
- Record timestamp of vote casting
- Provide validation of vote fields
- Serialize vote data for hashing

**Key Design Decisions**:
- Immutability: Once created, votes cannot be modified
- Timestamps are automatic to prevent manipulation
- Validation occurs at construction time

**Public Interface**:
```cpp
class Vote {
public:
    Vote(const std::string& voterId, const std::string& candidateName);
    std::string getVoterTempID() const;
    std::string getCandidate() const;
    std::time_t getTimestamp() const;
    bool isValid() const;
    std::string toString() const;
};
```

---

### 2. Block Class (`Block.h`, `Block.cpp`)

**Purpose**: Container for votes with cryptographic linking capability.

**Responsibilities**:
- Store multiple votes in a transaction batch
- Link to previous block via hash reference
- Calculate and maintain SHA-256 hash
- Validate block integrity
- Prevent duplicate voters within block

**Key Design Decisions**:
- Hash recalculation on any data change
- Genesis block factory method for chain initialization
- Automatic hash chaining

**Hash Calculation**:
```
Hash = SHA256(index + previousHash + timestamp + votes)
```

**Public Interface**:
```cpp
class Block {
public:
    Block(int idx, const std::string& prevHash);
    bool addVote(const Vote& vote);
    bool hasVoter(const std::string& voterTempID) const;
    bool isValid() const;
    std::string getHash() const;
    static Block createGenesisBlock();
};
```

---

### 3. Blockchain Class (`Blockchain.h`, `Blockchain.cpp`)

**Purpose**: Manages the complete blockchain and enforces voting rules.

**Responsibilities**:
- Maintain chain of blocks in correct order
- Validate new blocks before addition
- Detect duplicate voters across entire chain
- Verify chain integrity
- Provide statistics and analytics

**Key Design Decisions**:
- Genesis block auto-created on initialization
- Chain validation checks both hash integrity and linking
- Duplicate detection scans entire history

**Validation Process**:
1. Validate vote fields (non-empty, proper format)
2. Check for duplicate voter ID across all blocks
3. Check for duplicate voter ID in pending block
4. Add vote if all checks pass

**Public Interface**:
```cpp
class Blockchain {
public:
    Blockchain();
    void addBlock(Block newBlock);
    bool addVoteToPendingBlock(Block& pendingBlock, const Vote& vote);
    bool hasVoterVoted(const std::string& voterTempID) const;
    bool isChainValid() const;
    int getTotalVotes() const;
};
```

---

### 4. SHA256Helper Class (`SHA256Helper.h`, `SHA256Helper.cpp`)

**Purpose**: Cryptographic hashing utility using OpenSSL.

**Responsibilities**:
- Compute SHA-256 hashes from string input
- Convert binary hash to hexadecimal representation
- Provide consistent hashing interface

**Key Design Decisions**:
- Static methods for utility functionality
- Uses OpenSSL for industry-standard implementation
- Returns 64-character hex strings (256 bits)

**Security Properties**:
- **Deterministic**: Same input always produces same output
- **One-way**: Cannot reverse hash to get original data
- **Collision-resistant**: Extremely unlikely two inputs produce same hash
- **Avalanche effect**: Tiny input change produces completely different hash

---

### 5. VoteValidator Class (`VoteValidator.h`, `VoteValidator.cpp`)

**Purpose**: Centralized validation rules and error reporting.

**Responsibilities**:
- Validate voter ID format and length
- Validate candidate name format and length
- Provide detailed error messages
- Enforce security constraints

**Validation Rules**:
- Voter ID: 3-50 characters, alphanumeric + hyphen/underscore
- Candidate: 2-100 characters
- No whitespace-only strings
- No special characters that could cause injection attacks

**Public Interface**:
```cpp
struct ValidationResult {
    bool isValid;
    std::string errorMessage;
};

class VoteValidator {
public:
    static ValidationResult validateVoterID(const std::string& voterID);
    static ValidationResult validateCandidate(const std::string& candidate);
    static ValidationResult validateVote(const std::string& voterID, 
                                         const std::string& candidate);
};
```

---

## Data Flow

### Vote Submission Flow

```
1. User creates Vote object
   ↓
2. Vote.isValid() checks fields
   ↓
3. Blockchain.addVoteToPendingBlock() called
   ↓
4. VoteValidator validates format
   ↓
5. Blockchain.hasVoterVoted() scans chain
   ↓
6. Block.hasVoter() checks pending block
   ↓
7. Block.addVote() adds to pending block
   ↓
8. Block hash recalculated
   ↓
9. Block added to blockchain
   ↓
10. Chain validation confirms integrity
```

### Chain Validation Flow

```
1. For each block (starting from index 1):
   ↓
2. Check block's stored hash matches calculated hash
   ↓
3. Check block's previousHash matches actual previous block's hash
   ↓
4. Genesis block hash validated separately
   ↓
5. Return true if all checks pass
```

---

## Security Model

### Immutability Guarantees

1. **Vote Immutability**: Votes use `const` methods and private members
2. **Block Immutability**: Hash changes if any data changes
3. **Chain Immutability**: Modifying old blocks breaks hash chain
4. **Cryptographic Proof**: SHA-256 ensures tamper detection

### Attack Resistance

**Double-Voting Prevention**:
- Cross-block scan ensures one vote per voter ID
- O(n*m) complexity trade-off for guaranteed accuracy
- Future optimization: Hash set for O(1) lookup

**Data Tampering Detection**:
- Any modification changes block hash
- Hash chain breaks immediately
- `isChainValid()` detects tampering

**Invalid Vote Prevention**:
- Field validation rejects empty/malformed votes
- Length constraints prevent buffer overflows
- Character restrictions prevent injection attacks

---

## Performance Characteristics

### Time Complexity

| Operation | Complexity | Notes |
|-----------|------------|-------|
| Add Vote | O(n*m) | Scans chain for duplicates |
| Block Validation | O(k) | k = votes in block |
| Chain Validation | O(n*m) | Validates all blocks |
| Hash Calculation | O(d) | d = data size |

Where:
- n = number of blocks
- m = average votes per block
- k = votes in specific block
- d = total data in block

### Space Complexity

| Component | Space | Notes |
|-----------|-------|-------|
| Vote | O(1) | Fixed size per vote |
| Block | O(m) | m = votes in block |
| Blockchain | O(n*m) | Total votes in chain |
| Hash | O(1) | 64 bytes per hash |

---

## Design Patterns Used

### 1. Factory Pattern
```cpp
Block Block::createGenesisBlock();
```
- Encapsulates genesis block creation
- Ensures consistent initialization

### 2. Value Object Pattern
```cpp
class Vote {
    // Immutable once created
    const std::string voterTempID;
    const std::string candidate;
};
```
- Votes are value objects
- Equality based on content

### 3. Strategy Pattern
```cpp
class VoteValidator {
    static ValidationResult validate(...);
};
```
- Validation logic is pluggable
- Easy to extend validation rules

### 4. Chain of Responsibility
```cpp
validateFields() -> hasVoterVoted() -> hasVoter() -> addVote()
```
- Multiple validation stages
- Early exit on failure

---

## Future Enhancements

### 1. Performance Optimization
- Add hash set for O(1) voter lookup
- Implement vote indexing
- Add caching for frequent queries

### 2. Advanced Features
- Proof of Work consensus
- Merkle tree for efficient verification
- Smart contracts for automated rules
- Multi-signature authorization

### 3. Scalability
- Sharding for large-scale elections
- P2P network layer
- Distributed consensus
- Load balancing

### 4. Security Enhancements
- Digital signatures for voter authentication
- Zero-knowledge proofs for privacy
- Threshold cryptography
- Secure enclaves for key management

---

## Testing Strategy

### Unit Tests
- Vote validation
- Block hash calculation
- Chain validation
- Duplicate detection

### Integration Tests
- Multi-block scenarios
- Cross-block duplicate detection
- Chain integrity after tampering

### Security Tests
- Invalid vote rejection
- Duplicate vote prevention
- Tamper detection
- Hash collision resistance

---

## Deployment Considerations

### Production Requirements
1. **OpenSSL**: Must be installed and accessible
2. **C++11 Compiler**: GCC 4.8+, Clang 3.3+, MSVC 2015+
3. **Memory**: ~100MB for 100,000 votes
4. **Storage**: ~1GB for 1 million votes

### Configuration
- Block size: Configurable votes per block
- Validation rules: Customizable in VoteValidator
- Hash algorithm: Swappable (currently SHA-256)

---

## Maintenance

### Code Organization
- **Header files** (`include/`): Public interfaces
- **Source files** (`src/`): Implementation details
- **Main file** (`main.cpp`): Test and demonstration code

### Versioning
- Current version: 2.0.0
- Semantic versioning: MAJOR.MINOR.PATCH
- Git tags for releases

### Documentation
- Code comments: Explain "why" not "what"
- README: User-facing documentation
- ARCHITECTURE: This document
- COMPLEXITY_ANALYSIS: Performance details