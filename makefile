CC = clang
# CFLAGS = -Weverything -Wall -Wpedantic -std=c99 -Wextra -ggdb3 
CFLAGS = -Wall -Wpedantic -std=c99 -Wextra -ggdb3
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full

EXE = tisc
OBJ = tisc.o
INC = tisc.h

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(EXE)

clean:
	rm -rf $(EXE) $(OBJ)
