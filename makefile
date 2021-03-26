# TISC

CC = gcc
CFLAGS = -Wall -Wpedantic -std=c99 -Wextra -ggdb3 -I$(INC)
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full

# CC = clang
# CFLAGS = -Weverything -Wall -Wpedantic -std=c99 -Wextra -ggdb3 

PROJ = TISC

BIN = bin
SRC = src
INC = include

EXE = $(BIN)/$(PROJ)
OBJS = $(BIN)/$(PROJ).o

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN)/%.o: $(SRC)/%.c $(INC)/%.h
	$(CC) $(CFLAGS) $< -c -o $@

test: all
	./test.sh

lint:
	cppcheck --enable=all -Iinclude --inconclusive -v $(SRC)
	splint -Iinclude $(SRC)/*.c
	clang-tidy -checks=* $(SRC)/*.c -- -Iinclude
	diff -u <(clang-format $(INC)/*.h) <(cat $(INC)/*.h)
	diff -u <(clang-format $(SRC)/*.c) <(cat $(SRC)/*.c)

documentation:
	doxygen Doxyfile

clean:
	rm -rf $(BIN)/* html latex

.PHONY: all test documentation clean
