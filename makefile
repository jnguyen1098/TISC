# TISC

CC = clang
CFLAGS = -Wall -Wpedantic -std=c99 -Wextra -ggdb3 -I$(INC) \
# -Weverything
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full
SHELL = /bin/bash

PROJ = TISC

BIN = bin
INC = include
SRC = src
TESTS = tests

_OBJS = $(PROJ)

EXE = $(BIN)/$(PROJ)
DEPS = $(INC)/$(PROJ).h
OBJS = $(addprefix $(BIN)/,$(addsuffix .o,$(_OBJS)))

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN)/%.o: $(SRC)/%.c $(DEPS)
	$(CC) $(CFLAGS) $< -c -o $@

test: all
	cd $(TESTS) && ./run_tests.sh $$TESTARG

lint: all
	make cppcheck
	make splint
	make clang-analyze
	make clang-tidy
	make clang-format

cppcheck:
	@echo "Running cppcheck"
	cppcheck --enable=all -Iinclude --inconclusive -v $(SRC)

splint:
	@echo "Running splint"
	splint -Iinclude $(SRC)/*.c

clang-analyze:
	@echo "Running clang's static analyzer"
	clang --analyze src/*.c -Iinclude

clang-tidy:
	@echo "Running clang-tidy"
	clang-tidy -checks=* $(SRC)/*.c -- -Iinclude

clang-format:
	@echo "Running clang-format"
	diff -u <(clang-format $(INC)/*.h) <(cat $(INC)/*.h)
	diff -u <(clang-format $(SRC)/*.c) <(cat $(SRC)/*.c)

documentation:
	doxygen Doxyfile

clean:
	rm -rf $(BIN)/* $(TESTS)/tm html/ latex/ *.plist $(INC)/*.gch $(TESTS)/out/*

.PHONY: all test lint cppcheck splint clang-analyze\
        clang-tidy clang-format documentation clean
