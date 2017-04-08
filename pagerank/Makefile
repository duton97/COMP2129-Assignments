CC = clang
CFLAGS = -g -O1 -Wall -Werror -std=gnu11 -march=native
LDFLAGS = -lm -pthread

.PHONY: all clean

all: pagerank

pagerank: pagerank.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	-rm -f *.o
	-rm -f pagerank
	-rm -rf *.dSYM
