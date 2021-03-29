# TISC

CC = clang
CFLAGS = -Wall -Wpedantic -std=c99 -Wextra -ggdb3 -I$(INC) -Weverything
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full
SHELL = /bin/bash

PROJ = TISC

BIN = bin
INC = include
SRC = src
TESTS = tests

_OBJS = $(PROJ)

EXE = $(BIN)/$(PROJ)
DEPS = $(INC)/$(PROJ).h $(INC)/$(PROJ)_defs.h
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
	cppcheck --enable=all -I$(INC) --inconclusive -v $(SRC)

splint:
	@echo "Running splint"
	splint -I$(INC) $(SRC)/*.c +charint +matchanyintegral

clang-analyze:
	@echo "Running clang's static analyzer"
	clang --analyze $(SRC)/*.c -I$(INC)

clang-tidy:
	@echo "Running clang-tidy"
	clang-tidy -checks=* -header-filter=.* $(SRC)/*.c -- -I$(INC)

clang-format:
	@echo "Running clang-format"
	diff -u <(cat $(SRC)/*.c) <(clang-format $(SRC)/*.c)
	-diff -u <(cat $(INC)/*.h) <(clang-format $(INC)/*.h)

documentation:
	doxygen Doxyfile

clean:
	rm -rf $(BIN)/* $(TESTS)/tm html/ latex/ *.plist $(INC)/*.gch $(TESTS)/out/*

.PHONY: all test lint cppcheck splint clang-analyze\
        clang-tidy clang-format documentation clean
