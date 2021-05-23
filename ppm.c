// ppm.c
// Řešení IJC-DU1, příklad b), 28.2.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#include <stdio.h>
#include <stdlib.h>

#include "ppm.h"
#include "error.h"

struct ppm *ppm_read(const char *filename) {

    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        warning_msg("Error failed to load ppm file\n");
        return NULL;
    }

    char magic_number[3];
    int width;
    int height;
    int colors;

    // read format
    int res = fscanf(f, "%s %d %d %d ", magic_number, &width, &height, &colors);
    if (res == EOF) {
        warning_msg("Error: Failed to load ppm file format\n");
        fclose(f);
        return NULL;
    }

    if (magic_number[0] != 'P' 
            && magic_number[1] != '6' 
            && magic_number[2] != '\0') {
        warning_msg("Error: Unsupported ppm format, only P6 is supported\n");
        fclose(f);
        return NULL;
    }

    if (width < 1 || height < 1) {
        warning_msg("Error: Invalid dimensions of ppm file\n");
        fclose(f);
        return NULL;
    }

    if (colors != 255) {
        warning_msg("Error: Unsupported color depth\n");
        fclose(f);
        return NULL;
    }

    struct ppm *ppm = malloc(sizeof(struct ppm) + 3*width*height);
    if (ppm == NULL) {
        warning_msg("Error: Memory allocation failed\n");
        fclose(f);
        return NULL;
    }
    ppm->xsize = width;
    ppm->ysize = height;

    // read data
    int count = fread(ppm->data, 1, 3 * width * height, f);
    if (count != 3 * width * height) {
        warning_msg("Error: Failed to load ppm data\n");
        ppm_free(ppm);
        fclose(f);
        return NULL;
    }

    fclose(f);
    return ppm;
}

void ppm_free(struct ppm *p) {
    free(p);
}
