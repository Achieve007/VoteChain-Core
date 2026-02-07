# 🚀 API Quick Reference Card

## Base URL
```
http://localhost:8080
```

---

## 📊 Endpoints at a Glance

| Method | Endpoint | Purpose | Auth |
|--------|----------|---------|------|
| `POST` | `/addVote` | Submit vote | ❌ |
| `GET` | `/stats` | Get statistics | ❌ |
| `GET` | `/block/:id` | Get block | ❌ |
| `GET` | `/deadblock` | Rejected votes | ❌ |
| `GET` | `/validate` | Check integrity | ❌ |
| `GET` | `/` | API docs | ❌ |

---

## 📝 POST /addVote

**Submit a vote**

```bash
curl -X POST http://localhost:8080/addVote \
  -H "Content-Type: application/json" \
  -d '{"voterTempID":"VOTER-001","candidate":"Alice"}'
```

**Request:**
```json
{
  "voterTempID": "string (3-50 chars)",
  "candidate": "string (2-100 chars)",
  "timestamp": "number (optional)"
}
```

**Response:**
```json
{
  "status": "success|duplicate|invalid|error",
  "message": "Vote successfully recorded",
  "data": {
    "voterTempID": "VOTER-001",
    "candidate": "Alice",
    "blockIndex": 1,
    "blockHash": "3f78...",
    "timestamp": 1736679843
  },
  "meta": {
    "processingTime": 2.45,
    "serverTimestamp": 1736679843
  }
}
```

---

## 📈 GET /stats

**Get voting statistics**

```bash
curl http://localhost:8080/stats
```

**Response:**
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

## 🔍 GET /block/:index

**Get specific block**

```bash
curl http://localhost:8080/block/1
```

**Response:**
```json
{
  "status": "success",
  "blockIndex": 1,
  "blockHash": "a3f5...",
  "previousHash": "5fec...",
  "timestamp": 1736679900,
  "voteCount": 100,
  "votes": [
    {
      "voterTempID": "VOTER-001",
      "candidate": "Alice Johnson",
      "timestamp": 1736679850
    }
  ]
}
```

---

## 🗑️ GET /deadblock

**Get rejected votes**

```bash
curl http://localhost:8080/deadblock
```

**Response:**
```json
{
  "status": "success",
  "totalRejected": 30,
  "invalidCount": 15,
  "duplicateCount": 15,
  "exportJSON": "{...}"
}
```

---

## ✅ GET /validate

**Validate blockchain**

```bash
curl http://localhost:8080/validate
```

**Response:**
```json
{
  "status": "success",
  "chainValid": true,
  "message": "Blockchain integrity verified",
  "totalBlocks": 3,
  "totalVotes": 250
}
```

---

## 🎯 Status Codes

| Status | Meaning |
|--------|---------|
| `success` | Vote accepted ✅ |
| `duplicate` | Already voted ⚠️ |
| `invalid` | Invalid format ❌ |
| `error` | Server error 🔥 |

---

## 🔧 Common Errors

### Empty Voter ID
```json
{
  "status": "invalid",
  "rejectionReason": "Voter ID cannot be empty"
}
```

### Voter ID Too Short
```json
{
  "status": "invalid",
  "rejectionReason": "Voter ID too short (minimum 3 characters)"
}
```

### Duplicate Vote
```json
{
  "status": "duplicate",
  "rejectionReason": "Duplicate voter ID detected in blockchain"
}
```

---

## 🧪 Quick Test

```bash
# Start server
./api_server

# Submit vote
curl -X POST http://localhost:8080/addVote \
  -H "Content-Type: application/json" \
  -d '{"voterTempID":"TEST-001","candidate":"Alice"}'

# Check stats
curl http://localhost:8080/stats

# Try duplicate
curl -X POST http://localhost:8080/addVote \
  -H "Content-Type: application/json" \
  -d '{"voterTempID":"TEST-001","candidate":"Bob"}'
```

---

## ⚡ Performance

- **Processing**: 0.5-3ms per vote
- **Throughput**: ~1000 votes/sec
- **Threads**: 8 concurrent workers
- **Block Size**: 100 votes (auto-finalize)

---

## 🔐 Security Notes

⚠️ **Development Mode**: No authentication

**Production TODO:**
- Add JWT tokens
- Enable HTTPS/TLS
- Implement rate limiting
- Add CORS headers
- Input sanitization (already done)

---

## 📚 Full Documentation

See **API_DOCUMENTATION.md** for:
- Complete endpoint reference
- Security best practices
- Performance benchmarks
- Testing strategies
- Client examples (JS, Python, Go)

---

## 🆘 Troubleshooting

**Server won't start:**
```bash
# Check port 8080
netstat -an | grep 8080
```

**Connection refused:**
```bash
# Verify server running
ps aux | grep api_server
```

**Malformed JSON:**
```bash
# Use -v for verbose
curl -v http://localhost:8080/addVote
```

---

**Quick Reference v1.0.0** | **Server**: Crow C++ | **Port**: 8080