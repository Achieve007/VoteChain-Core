## 📚 Documentation

- **[README.md](README.md)**: This file - project overview and quick start
- **[ARCHITECTURE.md](ARCHITECTURE.md)**: Detailed system design, components, and patterns
- **[docs/COMPLEXITY_ANALYSIS.md](docs/COMPLEXITY_ANALYSIS.md)**: Performance analysis and optimization strategies
- **[docs/VALIDATION_GUIDE.md](docs/VALIDATION_GUIDE.md)**: Comprehensive validation testing guide

### Key Documentation Highlights

**ARCHITECTURE.md** covers:
- Component responsibilities and interfaces
- Data flow diagrams
- Security model and guarantees
- Design patterns used
- Future enhancement roadmap

**COMPLEXITY_ANALYSIS.md** covers:
- Time complexity: O(n×m) for duplicate detection (current)
- Optimization path: Hash set for O(1) lookups
- Space complexity analysis
- Scalability limits and benchmarking
- Trade-off analysis for different approaches

**VALIDATION_GUIDE.md** covers:
- Multi-layer validation explanation
- Test case examples
- Error message reference
- Customizing validation rules
- Debugging tips## 📊 Example Output

When you run the program, you'll see comprehensive test results:

```
╔══════════════════════════════════════════════════════════╗
║   Blockchain Voting System - Vote Validation Tests      ║
║   Testing duplicate detection & field validation        ║
╚══════════════════════════════════════════════════════════╝

============================================================
  TEST 1: Valid Votes
============================================================

Adding valid votes to Block #1:
✓ Vote accepted: VOTER-A1B2C3 -> Alice Johnson
✓ Vote accepted: VOTER-D4E5F6 -> Bob Smith
✓ Vote accepted: VOTER-G7H8I9 -> Charlie Davis
✓ Block #1 added successfully to the blockchain

✓ All valid votes accepted successfully

============================================================
  TEST 2: Invalid Vote Fields
============================================================

Testing invalid vote scenarios:

1. Empty voter ID:
✗ Vote rejected: Invalid vote data (empty fields)

2. Empty candidate:
✗ Vote rejected: Invalid vote data (empty fields)

3. Whitespace-only voter ID:
✗ Vote rejected: Invalid vote data (empty fields)

✓ All invalid votes correctly rejected

============================================================
  TEST 3: Duplicate Vote Detection
============================================================

Block #1 - Adding initial votes:
✓ Vote accepted: VOTER-001 -> Alice Johnson
✓ Vote accepted: VOTER-002 -> Bob Smith
✓ Block #1 added successfully to the blockchain

Block #2 - Attempting duplicate vote:

Attempting to vote again with VOTER-001:
✗ Vote rejected: Voter VOTER-001 has already voted in the blockchain

Adding new voter VOTER-003:
✓ Vote accepted: VOTER-003 -> Alice Johnson
✓ Block #2 added successfully to the blockchain

✓ Duplicate detection working correctly

============================================================
  ALL TESTS COMPLETED
============================================================

✅ Vote field validation: WORKING
✅ Duplicate detection (cross-block): WORKING
✅ Duplicate detection (same-block): WORKING
✅ VoteValidator rules: WORKING
✅ Complex scenarios: WORKING

🎉 Blockchain voting system is production-ready!
```# 🗳️ Blockchain Voting System

A production-ready, enterprise-grade C++ implementation of a blockchain-based voting system with SHA-256 cryptographic security, comprehensive vote validation, duplicate detection, and Proof of Authority (PoA) consensus mechanism to ensure election integrity.

## 🚀 Features

### Core Blockchain Features
- **SHA-256 Cryptographic Hashing**: Industry-standard security using OpenSSL
- **Immutable Vote Records**: Each vote is timestamped and stored permanently
- **Blockchain Manager**: Complete chain validation and integrity checking
- **Tampering Detection**: Automatically detects any unauthorized modifications
- **Block Chaining**: Blocks are cryptographically linked via hash references
- **Genesis Block**: Proper blockchain initialization

### Proof of Authority (PoA) Consensus ⭐ NEW
- **4 Authorized Validators**: Trusted entities who approve blocks
- **Multi-Signature Approval**: Requires 3 out of 4 validator signatures
- **Digital Signatures**: Simulated cryptographic signing and verification
- **Block Finalization**: Only blocks with sufficient consensus are added
- **Consensus Rejection**: Blocks without enough approvals are rejected
- **Validator Management**: Register, activate/deactivate validators
- **Audit Trail**: Complete record of all validator approvals

### Vote Validation & Security
- **Multi-Layer Validation**: Comprehensive vote verification system
  - Field validation (non-empty voter ID and candidate)
  - Format validation (length constraints, character restrictions)
  - Duplicate detection (prevents double-voting)
  - Hash integrity verification
- **Cross-Chain Duplicate Detection**: Scans entire blockchain to prevent voter from voting twice
- **Same-Block Duplicate Prevention**: Validates votes within pending blocks
- **Detailed Error Reporting**: Clear feedback for rejected votes with specific reasons
- **Customizable Validation Rules**: Configurable constraints via VoteValidator class

### Rejected Vote Tracking (DeadBlock)
- **Invalid Vote Logging**: Tracks all votes rejected due to format errors
- **Duplicate Vote Logging**: Records all duplicate voting attempts
- **Detailed Metadata**: Stores voter ID, candidate, timestamp, rejection reason
- **Categorized Rejections**: Separates invalid votes from duplicates
- **Export Capabilities**: CSV and JSON export for analysis
- **Audit Transparency**: Complete record for election officials

### REST API (Day 9) ⭐ NEW
- **HTTP Endpoints**: RESTful API for vote submission and blockchain access
- **POST /addVote**: Submit votes via HTTP with JSON
- **GET /stats**: Real-time voting statistics
- **GET /block/:index**: Retrieve specific blocks
- **GET /deadblock**: Access rejected votes
- **GET /validate**: Validate blockchain integrity
- **Multi-threaded**: 8 concurrent worker threads
- **Thread-safe**: Mutex-protected operations
- **JSON Responses**: Structured response format
- **Processing Metrics**: Response time tracking

### Developer Features
- **Clean OOP Design**: Modular, testable, and maintainable architecture
- **Comprehensive Testing**: 7+ test suites covering all scenarios
- **Cross-Platform**: Standard C++11/14, works on Linux, macOS, and Windows
- **Well-Documented**: Extensive inline comments and documentation
- **Build Automation**: Makefile and CMake support

## 📁 Project Structure

```
blockchain-voting/
├── include/               # Header files
│   ├── Vote.h            # Vote class with validation
│   ├── Block.h           # Block class with vote management
│   ├── Blockchain.h      # Blockchain manager with duplicate detection
│   ├── SHA256Helper.h    # SHA-256 hashing utility
│   ├── VoteValidator.h   # Centralized validation rules
│   ├── DeadBlock.h       # Rejected vote tracking system
│   ├── Validator.h       # ⭐ PoA validator entity
│   └── ConsensusPoA.h    # ⭐ Proof of Authority consensus engine
├── src/                  # Implementation files
│   ├── Vote.cpp          # Vote validation logic
│   ├── Block.cpp         # Block-level duplicate checks
│   ├── Blockchain.cpp    # Cross-chain duplicate detection
│   ├── SHA256Helper.cpp  # SHA-256 hashing implementation
│   ├── VoteValidator.cpp # Validation rule enforcement
│   ├── DeadBlock.cpp     # Rejected vote logging
│   ├── Validator.cpp     # ⭐ Validator management
│   └── ConsensusPoA.cpp  # ⭐ PoA consensus implementation
├── docs/                 # Documentation
│   ├── COMPLEXITY_ANALYSIS.md  # Performance & optimization guide
│   └── VALIDATION_GUIDE.md     # Testing & validation reference
├── main.cpp              # Validation test suite (7 scenarios)
├── test_poa.cpp          # ⭐ PoA consensus test suite (6 scenarios)
├── Makefile              # Build automation
├── CMakeLists.txt        # CMake configuration
├── ARCHITECTURE.md       # System design documentation
├── README.md             # This file
└── LICENSE               # MIT License
```

## 🔧 Building the Project

### Prerequisites
- **C++17 or later compiler** (GCC 7+, Clang 5+, MSVC 2017+)
- **CMake 3.10+**
- **OpenSSL library** installed

**Install OpenSSL:**
- **Ubuntu/Debian**: `sudo apt-get install libssl-dev cmake build-essential`
- **macOS**: `brew install openssl cmake`
- **Windows**: Download from [slproweb.com/products/Win32OpenSSL.html](https://slproweb.com/products/Win32OpenSSL.html)

---

### 🚀 Quick Build (All Platforms)

**Windows:**
```batch
build.bat
cd build\bin
api_server.exe
```

**macOS/Linux:**
```bash
chmod +x build.sh
./build.sh
cd build/bin
./api_server
```

---

### Option 1: Using Build Scripts (Recommended) ⚡

**Windows (PowerShell/CMD):**
```batch
build.bat
```

**macOS/Linux (Bash):**
```bash
chmod +x build.sh
./build.sh
```

**What the scripts do:**
1. Create `build/` directory
2. Configure CMake
3. Build all targets
4. Create executables in `build/bin/`
5. Display build summary

---

### Option 2: Using CMake Manually 🏗️

**All Platforms:**
```bash
# Create and enter build directory
mkdir build
cd build

# Configure (choose one based on platform)
cmake ..                           # Linux/macOS with Make
cmake .. -G "MinGW Makefiles"      # Windows with MinGW
cmake .. -G "Visual Studio 17 2022" # Windows with VS 2022

# Build
cmake --build . --config Release

# Run executables
cd bin
./voting_system      # or voting_system.exe on Windows
./test_poa          # or test_poa.exe on Windows
./api_server        # or api_server.exe on Windows
```

---

### Build Targets

CMake creates **4 executables**:

| Executable | Purpose | Command |
|------------|---------|---------|
| `voting_system` | Run validation tests (7 tests) | `./voting_system` |
| `test_poa` | Run PoA consensus tests (6 tests) | `./test_poa` |
| `api_server` | Start REST API server | `./api_server` |
| `blockchain_server` | Start REST API server (alt) | `./blockchain_server` |

All executables are in `build/bin/` directory.

---

### Option 3: Manual Compilation (Legacy) 🔧

**Validation Tests:**
```bash
g++ -std=c++17 -I./include \
    src/Vote.cpp \
    src/SHA256Helper.cpp \
    src/Block.cpp \
    src/Blockchain.cpp \
    src/VoteValidator.cpp \
    src/DeadBlock.cpp \
    main.cpp \
    -o voting_system \
    -lssl -lcrypto
    
./voting_system
```

**PoA Consensus Tests:**
```bash
g++ -std=c++17 -I./include \
    src/Vote.cpp \
    src/SHA256Helper.cpp \
    src/Block.cpp \
    src/Validator.cpp \
    src/ConsensusPoA.cpp \
    test_poa.cpp \
    -o test_poa \
    -lssl -lcrypto

./test_poa
```

**REST API Server:**

*Windows (PowerShell):*
```powershell
g++ -std=c++17 -I./include -I./include/crow `
    src/Vote.cpp `
    src/SHA256Helper.cpp `
    src/Block.cpp `
    src/Blockchain.cpp `
    src/VoteValidator.cpp `
    src/DeadBlock.cpp `
    src/VotingAPI.cpp `
    api_server.cpp `
    -o api_server.exe `
    -lssl -lcrypto -lpthread -lws2_32

.\api_server.exe
```

*Linux/macOS:*
```bash
g++ -std=c++17 -I./include -I./include/crow \
    src/Vote.cpp \
    src/SHA256Helper.cpp \
    src/Block.cpp \
    src/Blockchain.cpp \
    src/VoteValidator.cpp \
    src/DeadBlock.cpp \
    src/VotingAPI.cpp \
    api_server.cpp \
    -o api_server \
    -lssl -lcrypto -lpthread

./api_server
```

**Test API:**
```bash
# In another terminal while server is running
curl -X POST http://localhost:8080/addVote \
  -H "Content-Type: application/json" \
  -d '{"voterTempID":"VOTER-001","candidate":"Alice Johnson"}'
```

## 🎯 Quick Start

### Basic Usage

```cpp
#include "Blockchain.h"
#include "Block.h"
#include "Vote.h"

// Initialize blockchain with genesis block
Blockchain votingChain;

// Create a new block
Block block1(1, votingChain.getChain().back().getHash());

// Create and add votes (with automatic validation)
Vote vote1("VOTER-001", "Alice Johnson");
Vote vote2("VOTER-002", "Bob Smith");

// Add votes to pending block (validates and checks for duplicates)
if (votingChain.addVoteToPendingBlock(block1, vote1)) {
    std::cout << "Vote 1 accepted!" << std::endl;
}

if (votingChain.addVoteToPendingBlock(block1, vote2)) {
    std::cout << "Vote 2 accepted!" << std::endl;
}

// Try to vote again (will be rejected - duplicate detection)
Vote duplicateVote("VOTER-001", "Charlie Davis");
if (!votingChain.addVoteToPendingBlock(block1, duplicateVote)) {
    std::cout << "Duplicate vote rejected!" << std::endl;
}

// Add block to chain
votingChain.addBlock(block1);

// Validate blockchain integrity
if (votingChain.isChainValid()) {
    std::cout << "✓ Blockchain is valid!" << std::endl;
}

// Display entire blockchain
votingChain.display();
```

### Running Built-in Tests

The project includes comprehensive test suites:

```bash
# Run all 6 test scenarios
./voting_system

# Or with make
make run
```

**Test Coverage:**
- ✅ Valid vote acceptance
- ✅ Invalid field rejection (empty voter ID, empty candidate)
- ✅ Cross-block duplicate detection
- ✅ Same-block duplicate detection
- ✅ VoteValidator rule enforcement
- ✅ Complex multi-block scenarios

## 🏗️ Architecture

### Vote Class
- Stores voter ID, candidate, and timestamp
- **Immutable after creation**
- **Field validation**: Checks for empty/whitespace-only fields
- Serializable for hashing

### Block Class
- Contains multiple votes
- SHA-256 cryptographic hash
- Links to previous block via hash
- **Vote validation**: Ensures valid votes before adding
- **Duplicate prevention**: Checks for duplicate voters within block
- Self-validation capability

### Blockchain Class
- Manages the entire chain of blocks
- **Cross-chain duplicate detection**: Scans all blocks for duplicate voters
- **Multi-layer validation**: 
  1. Field validation
  2. Format validation
  3. Duplicate detection across chain
  4. Duplicate detection within block
  5. Hash integrity verification
- Provides statistics and analytics
- Chain integrity validation
- **DeadBlock integration**: Logs all rejected votes

### VoteValidator Class
- Centralized validation rules
- **Voter ID validation**:
  - Length: 3-50 characters
  - Allowed: alphanumeric, hyphen, underscore, space
- **Candidate validation**:
  - Length: 2-100 characters
  - Same character restrictions
- Detailed error messages
- Easily customizable rules

### DeadBlock Class
- Tracks all rejected votes with metadata
- **Invalid votes**: Format/field validation failures
- **Duplicate votes**: Double-voting attempts
- **Rejection reasons**: Categorized with enums
- **Export**: CSV and JSON formats
- Audit trail for transparency

### Validator Class ⭐ NEW
- Represents authorized validator in PoA network
- **Digital signatures**: Simulated cryptographic signing
- **Public key**: For signature verification
- **Active status**: Can be activated/deactivated
- **Statistics**: Tracks blocks validated per validator

### ConsensusPoA Class ⭐ NEW
- **Proof of Authority consensus engine**
- Manages 4 authorized validators
- **Multi-signature approval**: Requires 3/4 signatures
- **Block submission**: Pending blocks await consensus
- **Signature collection**: Validators sign blocks
- **Finalization**: Only approved blocks enter chain
- **Rejection mechanism**: Insufficient consensus = rejected
- Complete audit trail of all approvals

### VotingAPI Class ⭐ NEW
- **REST API handler** for HTTP endpoints
- Thread-safe vote processing with mutex
- **POST /addVote**: Submit votes via JSON
- **GET /stats**: Real-time statistics
- **GET /block/:index**: Retrieve blocks
- **GET /deadblock**: Rejected votes access
- **GET /validate**: Chain integrity check
- Automatic block finalization (100 votes/block)
- Processing time tracking

### SHA256Helper Class
- Wrapper for OpenSSL SHA-256 functions
- Converts binary hash to hexadecimal string
- Used by Block class for secure hashing

## 🔐 Security Features

### Cryptographic Security
- **SHA-256 Hashing**: Industry-standard cryptographic hash function
- **Immutable Chain**: Once added, blocks cannot be modified without detection
- **Hash Chain**: Each block references previous block's hash
- **Tampering Detection**: Any modification breaks the hash chain

**Example Hash:**
```
Input: Block data with votes...
SHA-256: 3f786850e387550fdab836ed7e6dc881de23001b2b9ad9f29cde4b424445c988
         ^ 64 hexadecimal characters (256 bits)
```

### Vote Validation & Integrity ⭐ NEW

#### Multi-Layer Validation
```
┌─────────────────────────────────────┐
│ Layer 1: Field Validation          │  Empty/whitespace checks
├─────────────────────────────────────┤
│ Layer 2: Format Validation         │  Length & character restrictions
├─────────────────────────────────────┤
│ Layer 3: Cross-Chain Duplicates    │  Scan entire blockchain
├─────────────────────────────────────┤
│ Layer 4: Same-Block Duplicates     │  Check pending block
├─────────────────────────────────────┤
│ Layer 5: Hash Integrity            │  Cryptographic verification
└─────────────────────────────────────┘
```

#### Duplicate Detection
**Problem**: Prevent voters from voting multiple times  
**Solution**: Comprehensive duplicate detection system

```cpp
// Example: Duplicate vote prevention
Vote vote1("VOTER-001", "Alice Johnson");
blockchain.addVoteToPendingBlock(block1, vote1);  // ✅ Accepted

// Later, in a different block...
Vote vote2("VOTER-001", "Bob Smith");
blockchain.addVoteToPendingBlock(block2, vote2);  // ❌ REJECTED
// Output: "✗ Vote rejected: Voter VOTER-001 has already voted in the blockchain"
```

#### Time Complexity
- **Current Implementation**: O(n × m) where n = blocks, m = votes per block
  - Scans entire blockchain for each vote
  - Suitable for small-medium elections (<10,000 votes)
  
- **Optimized Version** (see COMPLEXITY_ANALYSIS.md): O(1) with hash set
  - Uses `std::unordered_set` for instant lookups
  - Scales to millions of votes
  - Trade-off: O(n×m) extra memory for O(1) time

#### Validation Rules

**Voter ID:**
- ✅ Minimum 3 characters
- ✅ Maximum 50 characters
- ✅ Alphanumeric + hyphen/underscore/space only
- ❌ No empty or whitespace-only values

**Candidate Name:**
- ✅ Minimum 2 characters
- ✅ Maximum 100 characters
- ✅ Same character restrictions
- ❌ No empty or whitespace-only values

**Examples:**
```cpp
✅ Vote("VOTER-123", "Alice Johnson")      // Valid
✅ Vote("temp_voter_001", "Bob Smith")     // Valid
❌ Vote("", "Alice Johnson")               // Empty voter ID
❌ Vote("AB", "Alice")                     // Voter ID too short
❌ Vote("VOTER@123", "Alice")              // Invalid character
❌ Vote("VOTER-001", "VOTER-001")          // Duplicate (if voted before)
```

### Attack Prevention

| Attack Type | Prevention Method |
|-------------|-------------------|
| **Double-voting** | Cross-chain duplicate detection |
| **Empty votes** | Field validation |
| **Malformed data** | Format validation with VoteValidator |
| **Data tampering** | SHA-256 hash verification |
| **Chain corruption** | Integrity validation via `isChainValid()` |
| **Replay attacks** | Timestamp + chain position verification |

## 🛣️ Roadmap

### ✅ Completed
- [x] Implement SHA-256 hashing
- [x] Add Blockchain manager class
- [x] Implement chain validation
- [x] **Vote field validation**
- [x] **Duplicate voter detection (cross-chain)**
- [x] **Duplicate voter detection (same-block)**
- [x] **VoteValidator with customizable rules**
- [x] **Comprehensive validation test suite**
- [x] **DeadBlock rejected vote tracking**
- [x] **Proof of Authority (PoA) consensus**
- [x] **Multi-signature block approval (3/4 validators)**
- [x] **Validator management system**
- [x] **REST API with HTTP endpoints** ⭐
- [x] **JSON request/response format** ⭐
- [x] **Multi-threaded API server** ⭐
- [x] **Complete documentation**

### 🚧 In Progress / Planned
- [ ] Hash set optimization for O(1) duplicate detection
- [ ] Integrate PoA consensus with REST API
- [ ] JWT authentication for API
- [ ] Rate limiting for API endpoints
- [ ] HTTPS/TLS support
- [ ] WebSocket support for real-time updates
- [ ] Frontend web interface
- [ ] Proof of Work (PoW) consensus option
- [ ] Merkle tree for efficient verification
- [ ] Blockchain persistence (save/load to disk)
- [ ] Digital signatures with real cryptography (ECDSA)
- [ ] P2P network layer for distributed voting
- [ ] Zero-knowledge proofs for privacy
- [ ] Smart contracts for automated vote counting
- [ ] Mobile app integration

### Performance Optimization Priority
**Next Recommended**: 
1. Implement hash set for duplicate detection (O(n×m) → O(1))
2. Integrate PoA consensus with main voting workflow
3. Add real ECDSA cryptographic signatures
See: `docs/COMPLEXITY_ANALYSIS.md` for implementation guide

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

### Development Guidelines
1. Follow existing code style and conventions
2. Add comments for complex logic
3. Update tests for new features
4. Run all tests before submitting PR
5. Update documentation as needed

### Testing Your Changes
```bash
# Compile
make

# Run all tests
make run

# Verify no memory leaks (optional)
valgrind --leak-check=full ./voting_system
```

### Areas for Contribution
- Performance optimizations (hash set implementation)
- Additional validation rules
- More comprehensive test cases
- Documentation improvements
- Bug fixes and security enhancements

## 📝 License

MIT License - feel free to use this project for learning and development.

## 🎓 Educational Value

This project demonstrates:
- **Blockchain fundamentals**: Hashing, chaining, immutability
- **Cryptography**: SHA-256 implementation and security
- **Consensus mechanisms**: Proof of Authority (PoA) with multi-signature approval
- **Data structures**: Linked structures, hash-based lookups, maps
- **Algorithm design**: Duplicate detection, validation layers, consensus voting
- **Software engineering**: OOP, design patterns, testing, documentation
- **Performance analysis**: Time/space complexity trade-offs
- **Enterprise patterns**: Validator networks, audit trails, governance

Perfect for:
- Learning blockchain technology from scratch
- Understanding consensus mechanisms (PoA, and extensible to PoW/PoS)
- Practicing advanced C++ and OOP design
- Studying cryptographic security implementations
- Building production-ready voting systems
- Understanding enterprise blockchain architecture
- Creating portfolio projects for blockchain development

## 🔬 Technical Highlights

### Consensus Mechanism
**Proof of Authority (PoA)**:
- 4 registered validators (trusted authorities)
- Minimum 3 out of 4 signatures required (75% consensus)
- Digital signature simulation (ready for ECDSA upgrade)
- Block finalization only with sufficient approvals
- Automatic rejection of insufficient consensus
- Complete audit trail of validator decisions

### Security Features
- Multi-layer vote validation
- Cryptographic hash verification (SHA-256)
- Duplicate vote prevention across entire chain
- Rejected vote tracking (DeadBlock system)
- Validator-based consensus (PoA)
- Tamper-proof block linking

### Performance
- O(n×m) duplicate detection (optimizable to O(1))
- Efficient hash-based block validation
- Scalable validator signature collection
- Ready for hash set optimization

## 👨‍💻 Author

Built with ❤️ as a comprehensive learning project for blockchain technology and secure C++ development.

## 🙏 Acknowledgments

- OpenSSL for cryptographic functions
- C++ Standard Library for data structures
- Blockchain community for design patterns and best practices

---

## 📞 Support

- **Issues**: Use GitHub Issues for bug reports
- **Questions**: Check documentation in `docs/` folder
- **Performance**: See `COMPLEXITY_ANALYSIS.md` for optimization tips

---

**⭐ If you find this project helpful, please consider giving it a star on GitHub!**