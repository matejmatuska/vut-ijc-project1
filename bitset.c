#include <stdlib.h>
#include <stdio.h>

#include "bitset.h"

typedef struct {
    unsigned char *set;
    int size;
} bitset_t;

typedef unsigned long bitset_index_t;

void bitset_ctor(bitset_t *set, int bits) {
    int size = bits / 8 + 1;
    unsigned char *chars = malloc(size);
    if (chars == NULL) {
        exit(EXIT_FAILURE);
    }
    set->set = chars;
    set->size = size;
}

// gets value of the bit at index i
// returns 0 or 1
int  bitset_get(bitset_t *set, bitset_index_t i) {
    int byte = i / 8;
    int bit = i % 8;

    int mask = 1 << (8 - bit - 1);
    return (set->set[byte] & mask) != 0;
}

void bitset_set(bitset_t *set, bitset_index_t i, int exp) {
    int byte = i / 8;
    int bit = i % 8;

    int mask = 1 << (8 - bit - 1);
    if (exp) {
        set->set[byte] |= mask;
    } else {
        mask = ~mask; // invert mask
        set->set[byte] &= mask;
    }
}

int main() {

    bitset_t set;
    bitset_ctor(&set, 100);
    set.set[0] = 0;
    set.set[1] = 0;

    printf("%d\n", set.set[0]);
    printf("%d\n", set.set[1]);

    for (int i = 0; i < 16; i++) {
        if (i % 2 == 0) {
            bitset_set(&set, i, 1);
        }
    }

    printf("%d\n", set.set[0]);
    printf("%d\n", set.set[1]);

    for (int i = 0; i < 16; i++) {
        int val = bitset_get(&set, i);
        printf("%d", val);
    }

    return 0;
}