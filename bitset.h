#ifndef BITSET_H_
#define BITSET_H_

typedef struct {
    unsigned char *set;
    unsigned long size;
} bitset_t;

typedef unsigned long bitset_index_t;

//TODO error handling
#define bitset_alloc(jmeno_pole, velikost) \
    bitset_t (jmeno_pole); \
    int size = (velikost) / 8 + 1; \
    unsigned char *chars = malloc(size); \
    if (chars == NULL) { \
        exit(EXIT_FAILURE); \
    } \
    (jmeno_pole).set = chars; \
    (jmeno_pole).size = size; \

#define bitset_free(jmeno_pole) \
    free((jmeno_pole).set);

# define bitset_size(jmeno_pole) (jmeno_pole.size)

/*
#define bitset_getbit(jmeno_pole, index) \
    int byte = index / 8; \
    int bit = index % 8; \
    int mask = 1 << (8 - bit - 1); \
    (jmeno_pole.set[byte] & mask) != 0; \
*/

#define bitset_setbit(jmeno_pole, index, vyraz) \
    int byte = (index) / 8; \
    int bit = (index) % 8; \
    int mask = 1 << (8 - bit - 1); \
    if (vyraz) { \
        (jmeno_pole).set[byte] |= mask; \
    } else { \
        mask = ~mask; \
        (jmeno_pole).set[byte] &= mask; \
    } \

#define bitset_getbit(jmeno_pole, index) \
    (((jmeno_pole).set[(index) / 8] & (1 << (7 - (index) % 8))) != 0)

#endif
