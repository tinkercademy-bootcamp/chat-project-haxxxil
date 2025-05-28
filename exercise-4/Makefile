# Compiler and flags
CXX := g++
CXXFLAGS := -g -fsanitize=address -O3
LDFLAGS := -fsanitize=address

# Source files
SERVER_SRC := src/tcp_echo_server.cpp
CLIENT_SRC := src/tcp_echo_client.cpp
UTILS_SRC := src/utils.cc

# Output binaries
BUILD_DIR := build
SERVER_BIN := $(BUILD_DIR)/server
CLIENT_BIN := $(BUILD_DIR)/client

# Default target
all: $(SERVER_BIN) $(CLIENT_BIN)

# Build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build server
$(SERVER_BIN): $(SERVER_SRC) $(UTILS_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SERVER_SRC) $(UTILS_SRC) -o $(SERVER_BIN) $(LDFLAGS)

# Build client
$(CLIENT_BIN): $(CLIENT_SRC) $(UTILS_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CLIENT_SRC) $(UTILS_SRC) -o $(CLIENT_BIN) $(LDFLAGS)

# Clean target
clean:
	rm -rf $(BUILD_DIR)