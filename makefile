CC = clang
# CFLAGS = -Weverything -Wall -Wpedantic -std=c99 -Wextra -ggdb3 -Wnounused
CFLAGS = -Wall -Wpedantic -std=c99 -Wextra -ggdb3 -Wnounused
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full

EXE = tisc
OBJ = tisc.o

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(EXE)

%.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	rm -rf $(EXE) $(OBJ)
