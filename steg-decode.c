// steg-decode.c
// Řešení IJC-DU1, příklad b), 27.2.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1
// ...popis příkladu - poznámky, omezení, atd
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "bitset.h"
#include "eratosthenes.h"

#include "ppm.h"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Expected one argument!\n");
        return EXIT_FAILURE;
    }

    struct ppm *ppm = ppm_read(argv[1]);
    if (ppm == NULL) {
        return EXIT_FAILURE;
    }

    unsigned long size = 3 * ppm->xsize * ppm->ysize;
    bitset_alloc(arr, size);

    Eratosthenes(arr);

    bitset_index_t i = 23;
    unsigned char ch = 0;
    int bit_i = 0;

    while (i < size) {
        if (!bitset_getbit(arr, i)) {
            char byte = ppm->data[i];
            unsigned char mask = 1 << bit_i;
            if (byte & 1) {
                ch |= mask;
            } else {
                ch &= ~mask;
            }
            bit_i++;

            if (bit_i == CHAR_BIT) {
                putchar(ch);
                if (ch == '\0') {
                    putchar('\n');
                    bitset_free(arr);
                    ppm_free(ppm);
                    return EXIT_SUCCESS;
                }
                bit_i = 0;
            }
        }
        i++;
    }

    bitset_free(arr);
    ppm_free(ppm);
    //TODO error
    return EXIT_FAILURE;
}
