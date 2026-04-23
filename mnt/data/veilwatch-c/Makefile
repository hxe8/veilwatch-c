CC := cc
CFLAGS := -std=c11 -O2 -Wall -Wextra -Wpedantic -Iinclude
LDFLAGS := -lm
BIN_DIR := bin
SRC := src/main.c src/cli.c src/config.c src/parser.c src/analyze.c src/report.c
OBJ := $(SRC:.c=.o)
TARGET := $(BIN_DIR)/veilwatch

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: all
	./tests/smoke.sh

clean:
	rm -rf $(BIN_DIR) src/*.o tests/*.o
