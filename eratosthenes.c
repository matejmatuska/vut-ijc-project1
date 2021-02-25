#include <math.h>

#include "eratosthenes.h"
#include "bitset.h"

void Eratosthenes(bitset_t pole) {
    unsigned long N = bitset_size(pole);
    //TODO check size
    unsigned long sr = sqrt(N);

    for (bitset_index_t i = 2; i < sr; i++) {
        if (!bitset_getbit(pole, i)) {
            for (bitset_index_t j = i; j < N; j+=i) {
                bitset_setbit(pole, j, 1);
            }
        }
    }
}
