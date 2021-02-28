// primes.c
// Řešení IJC-DU1, příklad a), 28.2.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "eratosthenes.h"
#include "error.h"
#include "bitset.h"

#define N 200000000 // 200 milion

int main() {

    clock_t start = clock();

    bitset_create(pole, N);
    Eratosthenes(pole);

    // print primes
    bitset_index_t index = N - 1;
    int k = 0;
    while (k < 10 && index > 0) {
        int val = bitset_getbit(pole, index);
        if (!val) {
            printf("%lu\n", index);
            k++;
        }
        index--;
    }

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
