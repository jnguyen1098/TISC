CC = clang
# CFLAGS = -Weverything -Wall -Wpedantic -std=c99 -Wextra -ggdb3 
CFLAGS = -Wall -Wpedantic -std=c99 -Wextra -ggdb3 -Iinclude
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full

BIN = bin
SRC = src
INC = include

EXE = $(BIN)/TISC
OBJS = $(BIN)/TISC.o
SRCS = $(SRC)/TISC.c

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN)/%.o: $(SRC)/%.c $(INC)/%.h
	$(CC) $(CFLAGS) $< -c -o $@

test: all
	./test.sh

clean:
	rm -rf $(BIN)/*

.PHONY: all test clean
