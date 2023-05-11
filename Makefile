CC = gcc
CFLAGS = -Wall -Werror -g

SRC_DIR = src
BUILD_DIR = build

MAIN_SRC = $(SRC_DIR)/main.c
HACK_ENROLLMENT_SRC = $(SRC_DIR)/HackEnrollment.c
ISRAELI_QUEUES_SRC = $(SRC_DIR)/IsraeliQueues.c

MAIN_OBJ = $(BUILD_DIR)/main.o
HACK_ENROLLMENT_OBJ = $(BUILD_DIR)/HackEnrollment.o
ISRAELI_QUEUES_OBJ = $(BUILD_DIR)/IsraeliQueues.o

PROGRAM = HackEnrollment

.PHONY: all clean

all: $(PROGRAM)

$(PROGRAM): $(MAIN_OBJ) $(HACK_ENROLLMENT_OBJ) $(ISRAELI_QUEUES_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(HACK_ENROLLMENT_OBJ): $(HACK_ENROLLMENT_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(ISRAELI_QUEUES_OBJ): $(ISRAELI_QUEUES_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(PROGRAM)
