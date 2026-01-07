# 🗳️ VoteChain Core

A blockchain-based voting system built with C++ and Object-Oriented Programming (OOP).

## 📋 Project Overview

VoteChain Core is a secure, transparent voting system that uses blockchain technology to ensure:
- **Immutability**: Votes cannot be altered once recorded
- **Transparency**: All votes are verifiable
- **Security**: Proof of Authority (PoA) consensus mechanism
- **Duplicate Prevention**: Automatic detection of duplicate votes

## 🏗️ Project Structure

```
VOTECHAIN CORE/
├── include/          # Header files
│   ├── Block.h       # Block class definition
│   └── Vote.h        # Vote class definition
├── src/              # Source files
│   ├── Block.cpp     # Block implementation
│   └── Vote.cpp      # Vote implementation
├── main.cpp          # Main program
└── README.md         # This file
```

## 🚀 Features (In Development)

- ✅ **Day 1-2**: Genesis Block & Basic Structure
- 🔄 **Day 3-4**: SHA-256 Hashing & Blockchain Chain
- ⏳ **Day 5-6**: Vote Validation & Duplicate Detection
- ⏳ **Day 7**: Dead Block for Invalid Votes
- ⏳ **Day 8-9**: Proof of Authority (PoA) Consensus
- ⏳ **Day 10-11**: API Endpoint `/addVote`
- ⏳ **Day 12-13**: Logging & Testing

## 🔧 How to Compile

### Using g++:
```bash
g++ -std=c++11 main.cpp src/Vote.cpp src/Block.cpp -o voting_blockchain
./voting_blockchain
```

### Using MinGW (Windows):
```bash
g++ -std=c++11 main.cpp src/Vote.cpp src/Block.cpp -o voting_blockchain.exe
voting_blockchain.exe
```

## 📚 Technologies Used

- **Language**: C++11
- **Paradigm**: Object-Oriented Programming (OOP)
- **Hashing**: SHA-256 (coming in Day 3-4)
- **Consensus**: Proof of Authority (PoA)

## 📅 Development Timeline

**Start Date**: January 7, 2025  
**Deadline**: January 20, 2025  
**Status**: Day 1-2 Complete ✅

## 👨‍💻 Author

Developed as part of Blockchain Core Development learning journey.

## 📝 License

This project is for educational purposes.

---

**Last Updated**: January 7, 2025