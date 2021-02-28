// bitset.h
// Řešení IJC-DU1, příklad a), 28.2.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#ifndef BITSET_H_
#define BITSET_H_

#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "error.h"

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;

#define UL_BITS (CHAR_BIT * sizeof(unsigned long))

#define bitset_create(jmeno_pole, velikost) \
    unsigned long (jmeno_pole)[((velikost) / UL_BITS) + 2] = { 0, }; \
    (jmeno_pole)[0] = (velikost); \
    static_assert(((0 < velikost) && (velikost < ULONG_MAX)), "Velkost pola musi byt rozsahu unsigned long") \


#define bitset_alloc(jmeno_pole, velikost) \
    unsigned long *(jmeno_pole) = calloc((2 + ((velikost) / UL_BITS)), sizeof(unsigned long)); \
    if ((jmeno_pole) == NULL) { \
        fprintf(stderr, "bitset_alloc: Chyba alokace paměti\n"); \
        exit(EXIT_FAILURE); \
    } \
    (jmeno_pole)[0] = (velikost);  \


#ifdef USE_INLINE
    inline void bitset_free(bitset_t jmeno_pole) {
        free(jmeno_pole);
    }
#else
    #define bitset_free(jmeno_pole) (free(jmeno_pole))
#endif


#ifdef USE_INLINE
    inline unsigned long bitset_size(bitset_t jmeno_pole) {
        return jmeno_pole[0];
    }
#else
    # define bitset_size(jmeno_pole) ((jmeno_pole)[0])
#endif


#ifdef USE_INLINE
    inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz) {
        if (index > bitset_size(jmeno_pole)) {
            error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",
               (unsigned long)index, jmeno_pole[0]);
        }
        unsigned long byte = (index) / UL_BITS + 1;
        int bit = (index) % UL_BITS;
        unsigned long mask = 1UL << (UL_BITS - (bit) - 1);
        if (vyraz) {
            (jmeno_pole)[byte] |= mask;
        } else {
            mask = ~mask;
            (jmeno_pole)[byte] &= mask;
        }
    }
#else
    #define bitset_setbit(jmeno_pole, index, vyraz) \
        if (vyraz) { (jmeno_pole)[(index) / UL_BITS + 1] |= (1UL << (UL_BITS - (index) % UL_BITS - 1)); } else { (jmeno_pole)[(index) / UL_BITS + 1] &= ~(1UL << (UL_BITS - (index) % UL_BITS - 1)); }
#endif


#ifdef USE_INLINE
    inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index) {
        if (index > bitset_size(jmeno_pole)) {
            error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n",
               (unsigned long)index, jmeno_pole[0]);
        }
        unsigned long lindex = (index) / UL_BITS + 1;
        unsigned long mask = 1UL << (UL_BITS - ((index) % UL_BITS) - 1);
        return (jmeno_pole[lindex] & mask) != 0;
    }
#else
    #define bitset_getbit(jmeno_pole, index) ((index < 0 || index > bitset_size(jmeno_pole)) ? (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", index, jmeno_pole[0]), 0) : (((jmeno_pole)[(index) / UL_BITS + 1] & (1UL << (UL_BITS - ((index) % UL_BITS) - 1))) != 0))
#endif

#endif
