// eratosthenes.c
// Řešení IJC-DU1, příklad a), 28.2.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#include <math.h>

#include "eratosthenes.h"
#include "bitset.h"

// eratosthenove sito
// po vrateni funkcie budu v bitovom poli "pole"
// na indexoch prvocisel nastavene jednotlive bity na hodnotu "0"
void Eratosthenes(bitset_t pole) {
    unsigned long N = bitset_size(pole);
    unsigned long sroot = sqrt(N);

    bitset_setbit(pole, 0, 1);
    bitset_setbit(pole, 1, 1);

    for (bitset_index_t i = 2; i <= sroot; i++) {
        if (!bitset_getbit(pole, i)) {
            for (bitset_index_t j = i+i; j < N; j+=i) {
                bitset_setbit(pole, j, 1);
            }
        }
    }
}
