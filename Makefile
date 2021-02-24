CFLAGS= -std=c11 -pedantic -Wall -Wextra -g

all: bitset

bitset: bitset.o

bitset.o: bitset.c bitset.h

run: bitset
	./bitset

clean:
	rm bitset bitset.o
