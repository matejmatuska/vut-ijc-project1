// steg-encode.c
// Řešení IJC-DU1, příklad b), 28.2.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1
// Program na ocakava jeden argument - meno suboru PPM,
// do ktoreho sa ma sprava kodovat
// Spravu program nacita zo standardneho vstupu
// Subor PPM zo zakodovanou spravou je potom vypisany na standardny vystup
#include <stdio.h>
#include <stdlib.h>

#include "bitset.h"
#include "eratosthenes.h"

#include "ppm.h"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        error_exit("Ocakavane 1 argumenty\n");
    }

    struct ppm *ppm = ppm_read(argv[1]);
    if (ppm == NULL) {
        error_exit("Nepodarilo sa nacitat subor\n");
    }

    unsigned long size = 3 * ppm->xsize * ppm->ysize;
    bitset_alloc(arr, size);

    Eratosthenes(arr);

    bitset_index_t i = 23;

    //encode message in the data
    int ch;
    while (1) {
        if ((ch = getchar()) == EOF) {
            ch = '\0';
        }

        // write chars as individual bits
        char bit_i = 0;
        while (bit_i < CHAR_BIT && i < bitset_size(arr)) {
            if (!bitset_getbit(arr, i)) {
                unsigned char mask = 1 << bit_i;
                if (ch & mask) {
                    ppm->data[i] |= 1;
                } else {
                    ppm->data[i] &= ~1;
                }
                bit_i++;
            }
            i++;
        }
        if (ch == '\0' || i == bitset_size(arr)) {
            break;
        }
    }
    if (ch != '\0') {
        error_exit("Spravu sa nepodarilo spravne zakoncit\n");
    }

    // print the complete file to stdout
    printf("P6\n%d %d\n%d\n", ppm->xsize, ppm->ysize, 255);
    for (unsigned long i = 0; i < size; i++) {
        putchar(ppm->data[i]);
    }

    return EXIT_SUCCESS;
}
