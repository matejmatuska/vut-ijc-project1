#include <stdio.h>
#include <math.h>

#include "eratosthenes.h"
#include "bitset.h"

void Eratosthenes(bitset_t pole) {
    unsigned long N = bitset_size(pole);
    //TODO check size
    unsigned long sr = sqrt(N);
    bitset_setbit(pole, 1, 1);

    for (bitset_index_t i = 1; i < sr; i++) {
        if (!bitset_getbit(pole, i)) {
            for (bitset_index_t j = i*i; j < N; j+=i) {
                bitset_setbit(pole, j, 1);
            }
        }
    }

    // printing
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
}
