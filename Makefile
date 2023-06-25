CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC_DIR = src

all: example

example: $(SRC_DIR)/example.c $(SRC_DIR)/vector.c
	$(CC) $(CFLAGS) -o example $(SRC_DIR)/example.c $(SRC_DIR)/vector.c

.PHONY: clean
clean:
	rm -f example example.exe


