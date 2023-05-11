# Directories
SRC_DIR := src
BUILD_DIR := build

# Compiler options
CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11
LDFLAGS :=

# Source files
SRCS := \
    $(SRC_DIR)/main.c \
    $(SRC_DIR)/HackEnrollment.c \
    $(SRC_DIR)/IsraeliQueues.c \
    $(SRC_DIR)/capslock.c

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Executable
TARGET := $(BUILD_DIR)/my_program

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

# Linking target
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

# Compilation targets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $@

# Clean target
clean:
	rm -rf $(BUILD_DIR)

# Dependencies
$(BUILD_DIR)/HackEnrollment.o: $(SRC_DIR)/HackEnrollment.c $(SRC_DIR)/HackEnrollment.h $(SRC_DIR)/IsraeliQueues.h $(SRC_DIR)/headers.h $(SRC_DIR)/capslock.h
$(BUILD_DIR)/IsraeliQueues.o: $(SRC_DIR)/IsraeliQueues.c $(SRC_DIR)/IsraeliQueues.h $(SRC_DIR)/headers.h
$(BUILD_DIR)/capslock.o: $(SRC_DIR)/capslock.c $(SRC_DIR)/capslock.h
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/HackEnrollment.h $(SRC_DIR)/capslock.h $(SRC_DIR)/headers.h $(SRC_DIR)/IsraeliQueues.h
