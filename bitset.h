#ifndef BITSET_H_
#define BITSET_H_

#include <limits.h>
#include <assert.h>

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;

#define UL_BITS (CHAR_BIT * sizeof(unsigned long))

#define bitset_create(jmeno_pole, velikost) \
    unsigned long (jmeno_pole)[((velikost) / UL_BITS) + 2] = { 0, }; \
    (jmeno_pole)[0] = (velikost); \
    static_assert(((velikost > 0) && (velikost < ULONG_MAX)), "Pozadovana velikost je 0 nebo je mimo meze unsigned long.") \

//TODO error handling
#define bitset_alloc(jmeno_pole, velikost) \
    unsigned long *(jmeno_pole) = malloc(sizeof(unsigned long) * (2 + ((velikost) / UL_BITS))); \
    if ((jmeno_pole) == NULL) { \
        exit(EXIT_FAILURE); \
    } \
    (jmeno_pole)[0] = (velikost);  \


#ifdef USE_INLINE
    #define TODO
#else
    #define bitset_free(jmeno_pole) (free(jmeno_pole))
#endif


#ifdef USE_INLINE
    #define TODO
#else
    # define bitset_size(jmeno_pole) ((jmeno_pole)[0])
#endif

/* TODO na konci remove
#define bitset_getbit(jmeno_pole, index) \
    int byte = index / 8; \
    int bit = index % 8; \
    int mask = 1 << (8 - bit - 1); \
    (jmeno_pole.set[byte] & mask) != 0; \
*/

//#ifdef USE_INLINE
  //  #define TODO
//#else

#define bitset_setbit(jmeno_pole, index, vyraz) \
        unsigned long byte = ((index) / UL_BITS) + 1; \
        int bit = (index) % UL_BITS; \
        unsigned long mask = 1UL << (UL_BITS - (bit) - 1); \
        if (vyraz) { \
            (jmeno_pole)[byte] |= mask; \
        } else { \
            mask = ~mask; \
            (jmeno_pole)[byte] &= mask; \
        } \

/*
 #define bitset_setbit(jmeno_pole, index, vyraz) \
        if (vyraz) { \
            (jmeno_pole)[(index) / UL_BITS + 1] |= (1 << (UL_BITS - (index) % UL_BITS - 1)); \
        } else { \
            (jmeno_pole)[(index) / UL_BITS + 1] &= ~(1 << (UL_BITS - (index) % UL_BITS - 1)); \
        } \
*/
//#endif

#ifdef USE_INLINE
    #define TODO
#else
    #define bitset_getbit(jmeno_pole, index) \
        (((jmeno_pole)[(index) / UL_BITS + 1] & (1UL << (UL_BITS - ((index) % UL_BITS) - 1))) != 0)
#endif

#endif
