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

// initialize bitset jmeno_pole on stack
// all bits set to 0
#define bitset_create(jmeno_pole, velikost) \
    static_assert(((0 < velikost) && (velikost < ULONG_MAX)), "Velkost pola musi byt rozsahu unsigned long"); \
    unsigned long (jmeno_pole)[((velikost) / UL_BITS) + (((velikost) % UL_BITS) ? 2 : 1)] = { 0, }; \
    (jmeno_pole)[0] = (velikost); \


// dynamically alocate bitset jmeno_pole on heap
// all bits set to 0
#define bitset_alloc(jmeno_pole, velikost) \
    assert(0 < (velikost) && (velikost) < ULONG_MAX); \
    unsigned long *(jmeno_pole) = calloc(((velikost) / UL_BITS) + ((velikost) % UL_BITS ? 2 : 1), sizeof(unsigned long)); \
    if ((jmeno_pole) == NULL) { \
        fprintf(stderr, "bitset_alloc: Chyba alokace paměti\n"); \
        exit(EXIT_FAILURE); \
    } \
    (jmeno_pole)[0] = (velikost);  \


// frees memory of dynamically allocated bitset
#ifdef USE_INLINE
    inline void bitset_free(bitset_t jmeno_pole) {
        free(jmeno_pole);
    }
#else
    #define bitset_free(jmeno_pole) (free(jmeno_pole))
#endif

// returns size of bitset jmeno_pole in bits
#ifdef USE_INLINE
    inline unsigned long bitset_size(bitset_t jmeno_pole) {
        return jmeno_pole[0];
    }
#else
    # define bitset_size(jmeno_pole) ((jmeno_pole)[0])
#endif

// sets bit at index "index" according to "vyraz":
// vyraz == 0 -> 0
// vyraz != 0 -> 1
#ifdef USE_INLINE
    inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz) {
        if (index >= bitset_size(jmeno_pole)) {
            error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",
               (unsigned long) index, bitset_size(jmeno_pole) - 1);
        }
        unsigned long byte = (index) / UL_BITS + 1;
        int bit = (index) % UL_BITS;
        unsigned long mask = 1UL << (UL_BITS - (bit) - 1);
        if (vyraz) {
            (jmeno_pole)[byte] |= mask;
        } else {
            (jmeno_pole)[byte] &= ~mask;
        }
    }
#else
    #define bitset_setbit(jmeno_pole, index, vyraz) ((index >= bitset_size(jmeno_pole)) ? (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", index, bitset_size(jmeno_pole) - 1), 0) : ((vyraz) ? ((jmeno_pole)[(index) / UL_BITS + 1] |= (1UL << (UL_BITS - (index) % UL_BITS - 1))) : ((jmeno_pole)[(index) / UL_BITS + 1] &= ~(1UL << (UL_BITS - (index) % UL_BITS - 1)))))
#endif

// returns value of bit at index "index", either 1 or 0
#ifdef USE_INLINE
    inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index) {
        if (index >= bitset_size(jmeno_pole)) {
            error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n",
               (unsigned long)index, bitset_size(jmeno_pole) - 1);
        }
        unsigned long lindex = (index) / UL_BITS + 1;
        unsigned long mask = 1UL << (UL_BITS - ((index) % UL_BITS) - 1);
        return (jmeno_pole[lindex] & mask) != 0;
    }
#else
    #define bitset_getbit(jmeno_pole, index) ((index >= bitset_size(jmeno_pole)) ? (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", index, bitset_size(jmeno_pole) - 1), 0) : (((jmeno_pole)[(index) / UL_BITS + 1] & (1UL << (UL_BITS - ((index) % UL_BITS) - 1))) != 0))
#endif

#endif
