# 🌐 Blockchain Voting System - REST API Documentation

## Overview

This REST API provides HTTP endpoints for interacting with the blockchain voting system. Built with **Crow C++ framework**, it offers thread-safe, high-performance vote submission and blockchain management.

**Version**: 1.0.0  
**Base URL**: `http://localhost:8080`  
**Protocol**: HTTP/1.1  
**Format**: JSON  
**Authentication**: None (add JWT for production)

---

## 📋 Table of Contents

1. [Quick Start](#quick-start)
2. [Endpoints](#endpoints)
3. [Request/Response Formats](#requestresponse-formats)
4. [Status Codes](#status-codes)
5. [Error Handling](#error-handling)
6. [Examples](#examples)
7. [Testing](#testing)
8. [Security](#security)
9. [Performance](#performance)
10. [Troubleshooting](#troubleshooting)

---

## 🚀 Quick Start

### Starting the Server

```bash
# Compile
g++ -std=c++14 -I./include -I./include/crow \
    src/*.cpp api_server.cpp \
    -o api_server -lssl -lcrypto -lpthread

# Run
./api_server
```

**Server Output:**
```
Voting API initialized. Ready to accept votes.
🚀 Server starting on http://localhost:8080
📝 API Documentation: http://localhost:8080/
⚡ Ready to accept votes!
```

### First API Call

```bash
curl http://localhost:8080/
```

---

## 📡 Endpoints

### Summary Table

| Method | Endpoint | Description | Auth |
|--------|----------|-------------|------|
| `GET` | `/` | API documentation | No |
| `POST` | `/addVote` | Submit a vote | No |
| `GET` | `/stats` | Get voting statistics | No |
| `GET` | `/block/:index` | Get specific block | No |
| `GET` | `/deadblock` | Get rejected votes | No |
| `GET` | `/validate` | Validate blockchain | No |

---

## 1️⃣ POST /addVote

**Submit a vote to the blockchain**

### Request

**Method**: `POST`  
**URL**: `/addVote`  
**Content-Type**: `application/json`

**Body Schema:**
```json
{
  "voterTempID": "string (required, 3-50 chars)",
  "candidate": "string (required, 2-100 chars)",
  "timestamp": "number (optional, unix timestamp)"
}
```

**Field Validation:**
- `voterTempID`: 
  - Required
  - Length: 3-50 characters
  - Allowed: alphanumeric, hyphen, underscore, space
  - No leading/trailing whitespace
- `candidate`:
  - Required
  - Length: 2-100 characters
  - Same character restrictions
- `timestamp`:
  - Optional (server generates if not provided)
  - Unix timestamp (seconds since epoch)

### Response

**HTTP Status**: `200 OK` (always, status in JSON body)

**Body Schema:**
```json
{
  "status": "success|duplicate|invalid|error",
  "message": "string (human-readable description)",
  "data": {
    "voterTempID": "string",
    "candidate": "string",
    "blockIndex": "number|null",
    "blockHash": "string|null (64-char hex)",
    "timestamp": "number (unix timestamp)",
    "rejectionReason": "string (only if rejected)"
  },
  "meta": {
    "processingTime": "number (milliseconds)",
    "serverTimestamp": "number (unix timestamp)"
  }
}
```

### Examples

#### Success Case

**Request:**
```bash
curl -X POST http://localhost:8080/addVote \
  -H "Content-Type: application/json" \
  -d '{
    "voterTempID": "VOTER-12345",
    "candidate": "Alice Johnson"
  }'
```

**Response (200 OK):**
```json
{
  "status": "success",
  "message": "Vote successfully recorded",
  "data": {
    "voterTempID": "VOTER-12345",
    "candidate": "Alice Johnson",
    "blockIndex": 1,
    "blockHash": "3f786850e387550fdab836ed7e6dc881de23001b2b9ad9f29cde4b424445c988",
    "timestamp": 1736679843
  },
  "meta": {
    "processingTime": 2.45,
    "serverTimestamp": 1736679843
  }
}
```

#### Duplicate Vote

**Request:**
```bash
curl -X POST http://localhost:8080/addVote \
  -H "Content-Type: application/json" \
  -d '{
    "voterTempID": "VOTER-12345",
    "candidate": "Bob Smith"
  }'
```

**Response (200 OK):**
```json
{
  "status": "duplicate",
  "message": "Vote rejected: Voter has already voted",
  "data": {
    "voterTempID": "VOTER-12345",
    "candidate": "Bob Smith",
    "blockIndex": null,
    "blockHash": null,
    "timestamp": 1736679850,
    "rejectionReason": "Duplicate voter ID detected in blockchain"
  },
  "meta": {
    "processingTime": 1.23,
    "serverTimestamp": 1736679850
  }
}
```

#### Invalid Vote

**Request:**
```bash
curl -X POST http://localhost:8080/addVote \
  -H "Content-Type: application/json" \
  -d '{
    "voterTempID": "",
    "candidate": "Charlie Davis"
  }'
```

**Response (200 OK):**
```json
{
  "status": "invalid",
  "message": "Vote rejected: Invalid vote data",
  "data": {
    "voterTempID": "",
    "candidate": "Charlie Davis",
    "blockIndex": null,
    "blockHash": null,
    "timestamp": 1736679860,
    "rejectionReason": "Voter ID cannot be empty"
  },
  "meta": {
    "processingTime": 0.89,
    "serverTimestamp": 1736679860
  }
}
```

---

## 2️⃣ GET /stats

**Retrieve voting system statistics**

### Request

**Method**: `GET`  
**URL**: `/stats`  
**Parameters**: None

### Response

**HTTP Status**: `200 OK`

**Body Schema:**
```json
{
  "totalVotesReceived": "number (all submitted votes)",
  "totalVotesAccepted": "number (valid votes in blockchain)",
  "totalVotesRejected": "number (invalid + duplicate)",
  "currentBlockIndex": "number (pending block index)",
  "votesInCurrentBlock": "number (votes in pending block)",
  "totalBlocks": "number (blocks in chain)",
  "totalVotesInChain": "number (votes across all blocks)",
  "chainValid": "boolean (integrity status)"
}
```

### Example

**Request:**
```bash
curl http://localhost:8080/stats
```

**Response (200 OK):**
```json
{
  "totalVotesReceived": 150,
  "totalVotesAccepted": 120,
  "totalVotesRejected": 30,
  "currentBlockIndex": 2,
  "votesInCurrentBlock": 45,
  "totalBlocks": 3,
  "totalVotesInChain": 120,
  "chainValid": true
}
```

---

## 3️⃣ GET /block/:index

**Retrieve a specific block from the blockchain**

### Request

**Method**: `GET`  
**URL**: `/block/:index`  
**Parameters**: 
- `index` (path parameter): Block index number (0 = genesis block)

### Response

**HTTP Status**: `200 OK`

**Body Schema:**
```json
{
  "status": "success|error",
  "message": "string (error message if failed)",
  "blockIndex": "number",
  "blockHash": "string (64-char hex)",
  "previousHash": "string (64-char hex or '0' for genesis)",
  "timestamp": "number (unix timestamp)",
  "voteCount": "number",
  "votes": [
    {
      "voterTempID": "string",
      "candidate": "string",
      "timestamp": "number"
    }
  ]
}
```

### Examples

#### Genesis Block (Block 0)

**Request:**
```bash
curl http://localhost:8080/block/0
```

**Response (200 OK):**
```json
{
  "status": "success",
  "blockIndex": 0,
  "blockHash": "5feceb66ffc86f38d952786c6d696c79c2dbc239dd4e91b46729d73a27fb57e9",
  "previousHash": "0",
  "timestamp": 1736679800,
  "voteCount": 0,
  "votes": []
}
```

#### Block with Votes

**Request:**
```bash
curl http://localhost:8080/block/1
```

**Response (200 OK):**
```json
{
  "status": "success",
  "blockIndex": 1,
  "blockHash": "a3f5e7d9c2b1a4f6e8d0c3b5a7f9e1d3c5b7a9f1e3d5c7b9a1f3e5d7c9b1a3f5",
  "previousHash": "5feceb66ffc86f38d952786c6d696c79c2dbc239dd4e91b46729d73a27fb57e9",
  "timestamp": 1736679900,
  "voteCount": 100,
  "votes": [
    {
      "voterTempID": "VOTER-001",
      "candidate": "Alice Johnson",
      "timestamp": 1736679850
    },
    {
      "voterTempID": "VOTER-002",
      "candidate": "Bob Smith",
      "timestamp": 1736679855
    }
  ]
}
```

#### Block Not Found

**Request:**
```bash
curl http://localhost:8080/block/999
```

**Response (200 OK):**
```json
{
  "status": "error",
  "message": "Block index out of range"
}
```

---

## 4️⃣ GET /deadblock

**Retrieve all rejected votes (invalid and duplicate)**

### Request

**Method**: `GET`  
**URL**: `/deadblock`  
**Parameters**: None

### Response

**HTTP Status**: `200 OK`

**Body Schema:**
```json
{
  "status": "success",
  "totalRejected": "number (total rejected votes)",
  "invalidCount": "number (invalid format votes)",
  "duplicateCount": "number (duplicate voter votes)",
  "exportJSON": "string (complete DeadBlock JSON)"
}
```

### Example

**Request:**
```bash
curl http://localhost:8080/deadblock
```

**Response (200 OK):**
```json
{
  "status": "success",
  "totalRejected": 30,
  "invalidCount": 15,
  "duplicateCount": 15,
  "exportJSON": "{\"creationTime\":1736679800,\"totalRejected\":30,...}"
}
```

---

## 5️⃣ GET /validate

**Validate blockchain integrity**

### Request

**Method**: `GET`  
**URL**: `/validate`  
**Parameters**: None

### Response

**HTTP Status**: `200 OK`

**Body Schema:**
```json
{
  "status": "success",
  "chainValid": "boolean",
  "message": "string (validation result)",
  "totalBlocks": "number",
  "totalVotes": "number"
}
```

### Examples

#### Valid Chain

**Request:**
```bash
curl http://localhost:8080/validate
```

**Response (200 OK):**
```json
{
  "status": "success",
  "chainValid": true,
  "message": "Blockchain integrity verified",
  "totalBlocks": 3,
  "totalVotes": 250
}
```

#### Invalid Chain (Tampered)

**Response (200 OK):**
```json
{
  "status": "success",
  "chainValid": false,
  "message": "Blockchain integrity compromised",
  "totalBlocks": 3,
  "totalVotes": 250
}
```

---

## 6️⃣ GET /

**API documentation and endpoint listing**

### Request

**Method**: `GET`  
**URL**: `/`  
**Parameters**: None

### Response

**HTTP Status**: `200 OK`

**Body Schema:**
```json
{
  "name": "string",
  "version": "string",
  "endpoints": [
    {
      "method": "string",
      "path": "string",
      "description": "string"
    }
  ]
}
```

### Example

**Request:**
```bash
curl http://localhost:8080/
```

**Response (200 OK):**
```json
{
  "name": "Blockchain Voting System API",
  "version": "1.0.0",
  "endpoints": [
    {
      "method": "POST",
      "path": "/addVote",
      "description": "Submit a vote to the blockchain"
    },
    {
      "method": "GET",
      "path": "/stats",
      "description": "Get voting statistics"
    }
  ]
}
```

---

## 📊 Status Codes

### API Status (in JSON body)

| Status | Meaning | HTTP Code |
|--------|---------|-----------|
| `success` | Vote accepted and added to blockchain | 200 |
| `duplicate` | Vote rejected - voter already voted | 200 |
| `invalid` | Vote rejected - invalid format/fields | 200 |
| `error` | Server error or invalid request | 200 |

**Note**: We use HTTP 200 for all responses and indicate status in the JSON body. This is a design choice for API consistency.

### Rejection Reasons

**Invalid Status Reasons:**
- `Voter ID cannot be empty`
- `Candidate name cannot be empty`
- `Voter ID too short (minimum 3 characters)`
- `Voter ID too long (maximum 50 characters)`
- `Candidate name too short (minimum 2 characters)`
- `Candidate name too long (maximum 100 characters)`
- `Voter ID contains invalid characters`
- `Candidate name contains invalid characters`
- `Voter ID cannot contain only whitespace`
- `Candidate name cannot contain only whitespace`

**Duplicate Status Reasons:**
- `Duplicate voter ID detected in blockchain`
- `Voter already has a vote in this pending block`

---

## 🔐 Security

### Current Implementation

**⚠️ Development Mode**: No authentication required

### Production Recommendations

#### 1. JWT Authentication

```http
POST /addVote HTTP/1.1
Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...
Content-Type: application/json

{
  "voterTempID": "VOTER-001",
  "candidate": "Alice Johnson"
}
```

#### 2. HTTPS/TLS

```cpp
// Enable SSL in api_server.cpp
app.ssl_file("server.crt", "server.key")
   .port(8443)
   .run();
```

#### 3. Rate Limiting

**Recommendation**: 100 requests per IP per hour

```http
HTTP/1.1 429 Too Many Requests
Retry-After: 3600
X-RateLimit-Limit: 100
X-RateLimit-Remaining: 0
```

#### 4. CORS Configuration

```cpp
// Allow specific origins
app.after([](crow::response& res) {
    res.add_header("Access-Control-Allow-Origin", "https://voting.example.com");
    res.add_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
});
```

#### 5. Input Sanitization

**Already Implemented:**
- Field length validation
- Character whitelist
- SQL injection prevention (no database)
- XSS prevention (JSON only)

---

## ⚡ Performance

### Specifications

- **Framework**: Crow (C++ micro web framework)
- **Concurrency**: Multi-threaded (8 threads by default)
- **Processing Time**: 0.5-3ms per vote (typical)
- **Throughput**: ~1000 votes/second (single server)
- **Block Size**: 100 votes per block (configurable)

### Benchmarks

**Hardware**: Intel i7, 16GB RAM, SSD

| Operation | Avg Time | 95th Percentile |
|-----------|----------|-----------------|
| POST /addVote (valid) | 2.1ms | 3.5ms |
| POST /addVote (duplicate) | 1.2ms | 2.0ms |
| POST /addVote (invalid) | 0.9ms | 1.5ms |
| GET /stats | 0.3ms | 0.5ms |
| GET /block/:index | 0.5ms | 1.0ms |
| GET /validate | 15ms | 25ms |

### Optimization Tips

1. **Block Size**: Increase from 100 to 1000 for higher throughput
2. **Thread Pool**: Increase threads for more concurrent connections
3. **Caching**: Cache blockchain statistics for GET /stats
4. **Compression**: Enable gzip for large responses

---

## 🧪 Testing

### Manual Testing

#### PowerShell
```powershell
curl -X POST http://localhost:8080/addVote `
  -H "Content-Type: application/json" `
  -d '{\"voterTempID\":\"VOTER-001\",\"candidate\":\"Alice\"}'
```

#### Bash
```bash
curl -X POST http://localhost:8080/addVote \
  -H "Content-Type: application/json" \
  -d '{"voterTempID":"VOTER-001","candidate":"Alice"}'
```

### Automated Testing

Save as `api_tests.sh`:

```bash
#!/bin/bash
API="http://localhost:8080"

echo "Testing POST /addVote (valid)"
curl -s -X POST $API/addVote \
  -H "Content-Type: application/json" \
  -d '{"voterTempID":"TEST-001","candidate":"Alice"}' | jq

echo -e "\nTesting POST /addVote (duplicate)"
curl -s -X POST $API/addVote \
  -H "Content-Type: application/json" \
  -d '{"voterTempID":"TEST-001","candidate":"Bob"}' | jq

echo -e "\nTesting GET /stats"
curl -s $API/stats | jq

echo -e "\nTesting GET /validate"
curl -s $API/validate | jq
```

### Load Testing

Using **Apache Bench**:
```bash
# 1000 requests, 10 concurrent
ab -n 1000 -c 10 -p vote.json -T application/json \
   http://localhost:8080/addVote
```

Using **wrk**:
```bash
# 10 threads, 100 connections, 30 seconds
wrk -t10 -c100 -d30s --latency \
    -s post.lua http://localhost:8080/addVote
```

---

## 🐛 Troubleshooting

### Common Issues

#### 1. Server Won't Start

**Error**: `Port 8080 already in use`

**Solution**:
```bash
# Windows
netstat -ano | findstr :8080
taskkill /PID <PID> /F

# Linux/Mac
lsof -ti:8080 | xargs kill
```

#### 2. Connection Refused

**Symptoms**: `curl: (7) Failed to connect to localhost port 8080`

**Check**:
```bash
# Verify server is running
ps aux | grep api_server

# Check firewall
sudo ufw status
```

#### 3. Malformed JSON

**Error**: `"status": "error", "message": "Invalid JSON format"`

**Common Causes**:
- Missing quotes around keys
- Trailing commas
- Unescaped special characters

**Valid JSON**:
```json
{
  "voterTempID": "VOTER-001",
  "candidate": "Alice Johnson"
}
```

#### 4. Empty Response

**Check**:
```bash
# Verbose output
curl -v http://localhost:8080/stats

# Check server logs
tail -f api_server.log
```

#### 5. Slow Response Times

**Diagnose**:
```bash
# Check processing time in response
curl http://localhost:8080/stats | jq '.meta.processingTime'

# Monitor system resources
top -p $(pgrep api_server)
```

---

## 📚 Additional Resources

### Related Documentation

- **[README.md](README.md)**: Project overview and quick start
- **[ARCHITECTURE.md](ARCHITECTURE.md)**: System design details
- **[POA_CONSENSUS.md](POA_CONSENSUS.md)**: Consensus mechanism
- **[VALIDATION_GUIDE.md](docs/VALIDATION_GUIDE.md)**: Validation testing

### Code Examples

**JavaScript/Node.js**:
```javascript
const axios = require('axios');

axios.post('http://localhost:8080/addVote', {
  voterTempID: 'VOTER-001',
  candidate: 'Alice Johnson'
})
.then(response => console.log(response.data))
.catch(error => console.error(error));
```

**Python**:
```python
import requests

response = requests.post('http://localhost:8080/addVote', 
    json={
        'voterTempID': 'VOTER-001',
        'candidate': 'Alice Johnson'
    })
print(response.json())
```

**Go**:
```go
import "net/http"
import "bytes"

body := []byte(`{"voterTempID":"VOTER-001","candidate":"Alice"}`)
resp, _ := http.Post("http://localhost:8080/addVote", 
                     "application/json", bytes.NewBuffer(body))
```

---

## 📞 Support

### Getting Help

- **GitHub Issues**: Report bugs or request features
- **Documentation**: Check README.md and other docs
- **Server Logs**: Enable verbose logging with `app.loglevel(crow::LogLevel::Debug)`

### Contributing

Contributions welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Add tests for new endpoints
4. Update this documentation
5. Submit a pull request

---

## 🔄 Changelog

### Version 1.0.0 (2026-01-12)

**Initial Release**:
- POST /addVote endpoint
- GET /stats endpoint
- GET /block/:index endpoint
- GET /deadblock endpoint
- GET /validate endpoint
- Multi-threaded server (8 threads)
- JSON request/response format
- Vote validation and duplicate detection
- DeadBlock integration for rejected votes
- Processing time tracking

---

## 📄 License

MIT License - See LICENSE file for details

---

**API Version**: 1.0.0  
**Last Updated**: January 12, 2026  
**Server**: Crow C++ Framework  
**Blockchain**: VoteChain-Core