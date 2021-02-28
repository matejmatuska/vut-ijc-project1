CC=gcc
CFLAGS= -std=c11 -pedantic -Wall -Wextra -O2
LDFLAGS= -lm

all: primes primes-i steg-decode

primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) $(LDFLAGS)  $^ -o $@

primes-i: primes-i.o bitset-i.o eratosthenes-i.o error.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

bitset-i.o: bitset.c bitset.h error.h
	$(CC) $(CFLAGS) -c -DUSE_INLINE $< -o $@

primes.o: primes.c eratosthenes.h
primes-i.o: primes.c
	$(CC) $(CFLAGS) -c -DUSE_INLINE $< -o $@

eratosthenes.o: eratosthenes.c eratosthenes.h
eratosthenes-i.o: eratosthenes.c
	$(CC) $(CFLAGS) -c -DUSE_INLINE $< -o $@

error.o: error.c error.h

steg-decode: steg-decode.o ppm.o error.o eratosthenes.o

ppm.o: ppm.c ppm.h

run: primes primes-i
	./primes
	./primes-i

clean:
	-rm primes primes-i steg-decode *.o

pack:
	zip xmatus36.zip *.c *.h Makefile

.PHONY: clean pack run
