CC = gcc
CFLAGS = -I . -Wall -Wextra
LDFLAGS = -lncurses

BUILD_DIR = build

# Object files
OBJECTS = $(BUILD_DIR)/game_state.o \
		  $(BUILD_DIR)/display.o \
		  $(BUILD_DIR)/messages.o \
		  $(BUILD_DIR)/move.o \
		  $(BUILD_DIR)/main.o

# Executable name
TARGET = tri_kreig

# Default target
all: $(BUILD_DIR) $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS)  -o $@ $(LDFLAGS)

$(BUILD_DIR)/game_state.o: libs/game_state.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/display.o: libs/display.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/messages.o: libs/messages.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/move.o: libs/move.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean: 
	rm -rf $(BUILD_DIR)

.PHONY: all clean
