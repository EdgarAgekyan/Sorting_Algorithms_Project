SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: sorting

sorting: quick.c shell.c heap.c batcher.c set.c stats.c sorting.c
	$(CC) -o sorting quick.c shell.c heap.c batcher.c set.c stats.c sorting.c -lm

sorting.o: *.c
	$(CC) $(CFLAGS) -c *.c

clean:
	rm -f sorting *.o

format:
	clang-format -i -style=file *.[ch]

