CC = gcc
CFLAGS = -Wall -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SRC = $(wildcard $(SRC_DIR)/*.c)
EXEC = ordonnanceur
all: $(EXEC)
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f $(EXEC)