# 🔧 Build Guide - Cross-Platform Instructions

## Overview

This guide shows you how to build the Blockchain Voting System on **Windows**, **macOS**, and **Linux** using CMake.

---

## 🪟 Windows

### Prerequisites

1. **Install CMake**
   - Download: https://cmake.org/download/
   - Or via Chocolatey: `choco install cmake`

2. **Install MinGW-w64** (if not already installed)
   - Download: https://www.mingw-w64.org/
   - Or via MSYS2: https://www.msys2.org/

3. **Install OpenSSL**
   - Download: https://slproweb.com/products/Win32OpenSSL.html
   - Install to: `C:\Program Files\OpenSSL-Win64`

### Build Steps

#### Method 1: Using Build Script (Easiest)

```batch
build.bat
```

#### Method 2: Manual CMake

```batch
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build . --config Release
```

#### Method 3: Using Visual Studio

```batch
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

### Run Executables

```batch
cd build\bin
voting_system.exe
test_poa.exe
api_server.exe
```

---

## 🍎 macOS

### Prerequisites

1. **Install Homebrew** (if not already installed)
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

2. **Install Dependencies**
   ```bash
   brew install cmake openssl
   ```

### Build Steps

#### Method 1: Using Build Script (Easiest)

```bash
chmod +x build.sh
./build.sh
```

#### Method 2: Manual CMake

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(sysctl -n hw.ncpu)
```

### Run Executables

```bash
cd build/bin
./voting_system
./test_poa
./api_server
```

---

## 🐧 Linux

### Prerequisites

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install -y cmake build-essential libssl-dev
```

**Fedora/RHEL:**
```bash
sudo dnf install cmake gcc-c++ openssl-devel
```

**Arch Linux:**
```bash
sudo pacman -S cmake gcc openssl
```

### Build Steps

#### Method 1: Using Build Script (Easiest)

```bash
chmod +x build.sh
./build.sh
```

#### Method 2: Manual CMake

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
```

### Run Executables

```bash
cd build/bin
./voting_system
./test_poa
./api_server
```

---

## 🎯 Build Targets

The build system creates **4 executables**:

| Executable | Purpose | Test Suite |
|------------|---------|------------|
| `voting_system` | Validation tests | 7 tests |
| `test_poa` | PoA consensus tests | 6 tests |
| `api_server` | REST API server | - |
| `blockchain_server` | REST API server (alt name) | - |

---

## 📊 CMake Custom Targets

### Run Tests

```bash
# Run validation tests
cmake --build . --target run_tests

# Run PoA tests
cmake --build . --target run_poa

# Start API server
cmake --build . --target run_server
```

### Or using make (Linux/macOS)

```bash
cd build
make run_tests
make run_poa
make run_server
```

---

## 🔧 Build Options

### Debug Build

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```

### Release Build (Optimized)

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

### Specify Compiler

```bash
# Use Clang
cmake .. -DCMAKE_CXX_COMPILER=clang++

# Use GCC
cmake .. -DCMAKE_CXX_COMPILER=g++
```

### Parallel Build

```bash
# Linux/macOS
cmake --build . -j$(nproc)

# Windows (MinGW)
cmake --build . -j4
```

---

## 🐛 Troubleshooting

### OpenSSL Not Found

**Windows:**
```batch
cmake .. -DOPENSSL_ROOT_DIR="C:\Program Files\OpenSSL-Win64"
```

**macOS:**
```bash
cmake .. -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl
```

**Linux:**
```bash
sudo apt-get install libssl-dev
```

### Compiler Not Found

**Windows:**
- Ensure MinGW is in PATH
- Or use Visual Studio generator

**macOS:**
```bash
xcode-select --install
```

**Linux:**
```bash
sudo apt-get install build-essential
```

### CMake Version Too Old

```bash
# Check version
cmake --version

# Upgrade (Ubuntu)
sudo apt-get install cmake

# Upgrade (macOS)
brew upgrade cmake
```

### Link Errors (ws2_32 on Windows)

CMake automatically adds `ws2_32` on Windows. If you still get errors:

```batch
# Verify MinGW installation
where g++
where cmake
```

---

## 📁 Build Output Structure

```
build/
├── bin/                    # Executables
│   ├── voting_system
│   ├── test_poa
│   ├── api_server
│   └── blockchain_server
├── lib/                    # Libraries (if any)
├── CMakeFiles/            # CMake internal files
└── CMakeCache.txt         # CMake configuration cache
```

---

## 🧹 Clean Build

### Remove build directory

```bash
# Linux/macOS
rm -rf build

# Windows
rmdir /s /q build
```

### Rebuild from scratch

```bash
# Linux/macOS
rm -rf build && mkdir build && cd build && cmake .. && cmake --build .

# Windows
rmdir /s /q build && mkdir build && cd build && cmake .. -G "MinGW Makefiles" && cmake --build .
```

---

## 🚀 Quick Start Summary

### Windows
```batch
build.bat
cd build\bin
api_server.exe
```

### macOS/Linux
```bash
./build.sh
cd build/bin
./api_server
```

---

## 📊 Verify Build

After building, verify all executables:

```bash
cd build/bin

# Check files exist
ls -lh                    # Linux/macOS
dir                       # Windows

# Test executables
./voting_system --help    # Should show usage or run tests
./test_poa               # Should run PoA tests
./api_server &           # Should start server
```

---

## 🔍 CMake Configuration Summary

CMake automatically detects and configures:

- ✅ **Platform**: Windows, macOS, or Linux
- ✅ **Compiler**: MSVC, GCC, Clang
- ✅ **OpenSSL**: Library paths and includes
- ✅ **Threading**: pthread (Unix) or native (Windows)
- ✅ **Networking**: ws2_32 (Windows) or POSIX sockets
- ✅ **Warnings**: Platform-appropriate warning flags

---

## 📚 Additional Resources

- **CMake Documentation**: https://cmake.org/documentation/
- **OpenSSL Installation**: https://www.openssl.org/source/
- **MinGW-w64**: https://www.mingw-w64.org/
- **MSYS2** (Windows): https://www.msys2.org/

---

## 🆘 Getting Help

If you encounter issues:

1. Check CMake output for error messages
2. Verify all prerequisites are installed
3. Try a clean build (`rm -rf build`)
4. Check the troubleshooting section above
5. Review CMakeLists.txt for configuration details

---

**Happy Building!** 🔨✨

*Build once, run anywhere!*