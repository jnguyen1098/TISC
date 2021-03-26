CC = clang
# CFLAGS = -Weverything -Wall -Wpedantic -std=c99 -Wextra -ggdb3 
CFLAGS = -Wall -Wpedantic -std=c99 -Wextra -ggdb3
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full

EXE = TISC
OBJ = TISC.o
INC = TISC.h

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(EXE)

run: all
	./$(EXE) gcd.tm

clean:
	rm -rf $(EXE) $(OBJ)

.PHONY: all run clean
