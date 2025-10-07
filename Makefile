.PHONY: all clean
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O3

all: bin

BIN_OBJ = bin.o bin_dfs.o

bin: $(BIN_OBJ)
	$(CC) $(BIN_OBJ) -o $@
	rm -f $(BIN_OBJ)

bin.o: bin.c bin_dfs.h
bin_dfs.o: bin_dfs.c bin_dfs.h

clean:
	rm -f $(BIN_OBJ)
	rm -f bin

