# 🗳️ Blockchain Voting System

A clean, object-oriented C++ implementation of a blockchain-based voting system with immutable vote records and cryptographic hash linking.

## 🚀 Features

- **SHA-256 Cryptographic Hashing**: Industry-standard security using OpenSSL
- **Immutable Vote Records**: Each vote is timestamped and stored permanently
- **Blockchain Manager**: Complete chain validation and integrity checking
- **Tampering Detection**: Automatically detects any unauthorized modifications
- **Block Chaining**: Blocks are cryptographically linked via hash references
- **Genesis Block**: Proper blockchain initialization
- **Clean OOP Design**: Modular, testable, and maintainable architecture
- **Cross-Platform**: Standard C++11/14, works on Linux, macOS, and Windows

## 📁 Project Structure

```
blockchain-voting/
├── include/               # Header files
│   ├── Vote.h            # Vote class declaration
│   ├── Block.h           # Block class declaration
│   ├── Blockchain.h      # Blockchain manager class
│   └── SHA256Helper.h    # SHA-256 hashing utility
├── src/                  # Implementation files
│   ├── Vote.cpp          # Vote class implementation
│   ├── Block.cpp         # Block class implementation
│   ├── Blockchain.cpp    # Blockchain manager implementation
│   └── SHA256Helper.cpp  # SHA-256 hashing implementation
└── main.cpp              # Test driver program
```

## 🔧 Building the Project

### Prerequisites
- C++11 or later compiler (GCC, Clang, MSVC)
- OpenSSL library installed

**Install OpenSSL:**
- **Ubuntu/Debian**: `sudo apt-get install libssl-dev`
- **macOS**: `brew install openssl`
- **Windows**: Download from [slproweb.com/products/Win32OpenSSL.html](https://slproweb.com/products/Win32OpenSSL.html)

### Option 1: Using G++/Clang

```bash
g++ -std=c++11 -I./include \
    src/Vote.cpp \
    src/SHA256Helper.cpp \
    src/Block.cpp \
    src/Blockchain.cpp \
    main.cpp \
    -o voting_system \
    -lssl -lcrypto
    
./voting_system
```

### Option 2: Using CMake (Recommended)

```bash
mkdir build && cd build
cmake ..
make
./voting_system
```

**CMakeLists.txt:**
```cmake
cmake_minimum_required(VERSION 3.10)
project(BlockchainVoting)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenSSL REQUIRED)

include_directories(include ${OPENSSL_INCLUDE_DIR})

add_executable(voting_system 
    src/Vote.cpp
    src/SHA256Helper.cpp
    src/Block.cpp
    src/Blockchain.cpp
    main.cpp
)

target_link_libraries(voting_system ${OPENSSL_LIBRARIES})
```

## 🎯 Quick Start

```cpp
#include "Blockchain.h"
#include "Block.h"
#include "Vote.h"

// Initialize blockchain with genesis block
Blockchain votingChain;

// Create a new block
Block block1(1, votingChain.getChain().back().getHash());

// Add votes
Vote vote1("VOTER-001", "Alice Johnson");
Vote vote2("VOTER-002", "Bob Smith");
block1.addVote(vote1);
block1.addVote(vote2);

// Add block to chain
votingChain.addBlock(block1);

// Validate blockchain integrity
if (votingChain.isChainValid()) {
    std::cout << "Blockchain is valid!" << std::endl;
}

// Display entire blockchain
votingChain.display();
```

## 🏗️ Architecture

### Vote Class
- Stores voter ID, candidate, and timestamp
- Immutable after creation
- Serializable for hashing

### Block Class
- Contains multiple votes
- SHA-256 cryptographic hash
- Links to previous block via hash
- Self-validation capability

### Blockchain Class
- Manages the entire chain of blocks
- Validates chain integrity
- Detects tampering attempts
- Provides statistics and analytics

### SHA256Helper Class
- Wrapper for OpenSSL SHA-256 functions
- Converts binary hash to hexadecimal string
- Used by Block class for secure hashing

## 🔐 Security Features

- **SHA-256 Hashing**: Industry-standard cryptographic hash function
- **Immutable Chain**: Once added, blocks cannot be modified without detection
- **Tampering Detection**: Any modification breaks the hash chain
- **Cryptographic Linking**: Each block references previous block's hash
- **Chain Validation**: Full integrity check of entire blockchain

**Example Hash:**
```
Input: Block data with votes...
SHA-256: 3f786850e387550fdab836ed7e6dc881de23001b2b9ad9f29cde4b424445c988
         ^ 64 hexadecimal characters (256 bits)
```

## 🛣️ Roadmap

- [x] Implement SHA-256 hashing ✅
- [x] Add Blockchain manager class ✅
- [x] Implement chain validation ✅
- [ ] Add proof-of-work consensus (mining)
- [ ] Implement vote validation and double-vote prevention
- [ ] Add Merkle tree for efficient verification
- [ ] Implement blockchain persistence (save/load)
- [ ] Create REST API interface
- [ ] Add web-based voting frontend
- [ ] Implement P2P network layer

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📝 License

MIT License - feel free to use this project for learning and development.

## 👨‍💻 Author

Built with ❤️ as a learning project for blockchain and C++ development.