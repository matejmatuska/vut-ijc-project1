#ifndef BITSET_H_
#define BITSET_H_

#include <limits.h>

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;

#define ULONG_SIZE sizeof(unsigned long)
#define UL_BITS sizeof(CHAR_BITS * sizeof(unsigned long))

#define bitset_create(jmeno_pole, velikost) \
    unsigned long (jmeno_pole)[ULONG_SIZE * ((velikost) / ULONG_SIZE + 1)] = { 0, }; \
    (jmeno_pole)[0] = (velikost); \

//TODO error handling
#define bitset_alloc(jmeno_pole, velikost) \
    int size = (velikost) / ULONG_SIZE + 1; \
    unsigned long *(jmeno_pole) = malloc(ULONG_SIZE * size); \
    if ((jmeno_pole) == NULL) { \
        exit(EXIT_FAILURE); \
    } \
    (jmeno_pole)[0] = (velikost);  \

#define bitset_free(jmeno_pole) \
    free(jmeno_pole);

# define bitset_size(jmeno_pole) (jmeno_pole)[0]

/* TODO na konci remove
#define bitset_getbit(jmeno_pole, index) \
    int byte = index / 8; \
    int bit = index % 8; \
    int mask = 1 << (8 - bit - 1); \
    (jmeno_pole.set[byte] & mask) != 0; \
*/

#define bitset_setbit(jmeno_pole, index, vyraz) \
    int byte = (index) / 8 + 1; \
    int bit = (index) % 8; \
    int mask = 1 << (8 - bit - 1); \
    if (vyraz) { \
        (jmeno_pole)[byte] |= mask; \
    } else { \
        mask = ~mask; \
        (jmeno_pole)[byte] &= mask; \
    } \

#define bitset_getbit(jmeno_pole, index) \
    (((jmeno_pole)[(index) / 8 + 1] & (1 << (7 - (index) % 8))) != 0)

#endif
