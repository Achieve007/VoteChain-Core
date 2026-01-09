# 🗳️ Blockchain Voting System

A clean, object-oriented C++ implementation of a blockchain-based voting system with immutable vote records and cryptographic hash linking.

## 🚀 Features

- **Immutable Vote Records**: Each vote is timestamped and stored permanently
- **Block Chaining**: Blocks are cryptographically linked via hash references
- **Genesis Block**: Proper blockchain initialization
- **Clean OOP Design**: Modular, testable, and maintainable architecture
- **Cross-Platform**: Standard C++11/14, works on Linux, macOS, and Windows

## 📁 Project Structure

```
blockchain-voting/
├── include/          # Header files
│   ├── Vote.h       # Vote class declaration
│   └── Block.h      # Block class declaration
├── src/             # Implementation files
│   ├── Vote.cpp     # Vote class implementation
│   └── Block.cpp    # Block class implementation
└── main.cpp         # Test driver program
```

## 🔧 Building the Project

### Option 1: Using G++/Clang

```bash
g++ -std=c++11 -I./include src/Vote.cpp src/Block.cpp main.cpp -o voting_system
./voting_system
```

### Option 2: Using MSVC (Windows)

```bash
cl /EHsc /std:c++14 /I.\include src\Vote.cpp src\Block.cpp main.cpp /Fe:voting_system.exe
voting_system.exe
```

### Option 3: Using CMake (Recommended)

```bash
mkdir build && cd build
cmake ..
make
./voting_system
```

## 🎯 Quick Start

```cpp
#include "Block.h"
#include "Vote.h"

// Create genesis block
Block genesisBlock = Block::createGenesisBlock();

// Add votes
Vote vote1("VOTER-001", "Alice Johnson");
genesisBlock.addVote(vote1);

// Display block
genesisBlock.display();
```

## 🏗️ Architecture

### Vote Class
- Stores voter ID, candidate, and timestamp
- Immutable after creation
- Serializable for hashing

### Block Class
- Contains multiple votes
- Links to previous block via hash
- Automatically recalculates hash on changes
- Genesis block factory method

## 🔐 Security Note

Currently uses a **polynomial rolling hash** for demonstration. For production use, replace with **SHA-256** or another cryptographic hash function.

## 🛣️ Roadmap

- [ ] Implement SHA-256 hashing
- [ ] Add Blockchain manager class
- [ ] Implement proof-of-work consensus
- [ ] Add vote validation and double-vote prevention
- [ ] Implement blockchain persistence
- [ ] Add Merkle tree for efficient verification
- [ ] Create REST API interface

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📝 License

MIT License - feel free to use this project for learning.

## 👨‍💻 Author

Built with ❤️ as a learning project for blockchain and C++ development.