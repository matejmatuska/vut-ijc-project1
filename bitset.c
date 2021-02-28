// bitset.c
// Řešení IJC-DU1, příklad a), 28.2.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#include "bitset.h"

extern inline unsigned long bitset_size(bitset_t jmeno_pole);

extern inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz);

extern inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);

extern inline void bitset_free(bitset_t jmeno_pole);
