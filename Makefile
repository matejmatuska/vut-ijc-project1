CFLAGS= -std=c11 -pedantic -Wall -Wextra -g -lm

all: primes

primes: primes.o eratosthenes.o
	$(CC) $(CFLAGS) $^ -o $@

primes.o: primes.c eratosthenes.h bitset.h

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h


run: primes
	./primes

clean:
	rm primes primes.o eratosthenes.o
