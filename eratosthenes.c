#include <math.h>

#include "eratosthenes.h"
#include "bitset.h"

void Eratosthenes(bitset_t pole) {
    unsigned long N = bitset_size(pole);
    //TODO check size
    unsigned long sr = sqrt(N);

    bitset_setbit(pole, 0, 1);
    bitset_setbit(pole, 1, 1);

    for (bitset_index_t i = 2; i <= sr; i++) {
        if (!bitset_getbit(pole, i)) {
            for (bitset_index_t j = i+i; j < N; j+=i) {
                bitset_setbit(pole, j, 1);
            }
        }
    }
}
