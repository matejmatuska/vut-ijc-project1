#include <stdlib.h>
#include <stdio.h>

#include "bitset.h"

/*
typedef struct {
    unsigned char *set;
    int size;
} bitset_t;

typedef unsigned long bitset_index_t;
*/
/*
void bitset_ctor(bitset_t *set, int bits) {
    int size = bits / 8 + 1;
    unsigned char *chars = malloc(size);
    if (chars == NULL) {
        exit(EXIT_FAILURE);
    }
    set->set = chars;
    set->size = size;
}
*/

/*
// gets value of the bit at index i
// returns 0 or 1
int  bitset_get(bitset_t *set, bitset_index_t i) {
    int byte = i / 8;
    int bit = i % 8;

    int mask = 1 << (8 - bit - 1);
    return (set->set[byte] & mask) != 0;
}
*/

/*
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
*/

int main() {

    bitset_create(set, 200000000);

    printf("Size = %lu\n", bitset_size(set));
    set[1] = 0;
    set[2] = 1;

    printf("%lu\n", set[1]);
    printf("%lu\n", set[2]);

    for (int i = 0; i < 16; i++) {
        if (i % 2 == 0) {
            bitset_setbit(set, i, 1);
        }
    }

    printf("%lu\n", set[1]);
    printf("%lu\n", set[2]);

    for (int i = 0; i < 16; i++) {
        int val = bitset_getbit(set, i);
        printf("%d", val);
    }
    printf("Size = %lu\n", bitset_size(set));

    //bitset_free(set)


    return 0;
}
