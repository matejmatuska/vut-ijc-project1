#include <stdio.h>
#include <stdlib.h>

#include "ppm.h"
#include "error.h"

struct ppm *ppm_read(const char *filename) {

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        warning_msg("Nepodarilo sa otvorit subor\n");
        return NULL;
    }

    char magic_number[3];
    int width;
    int height;
    int colors;

    int res = fscanf(f, "%s %d %d %d ", magic_number, &width, &height, &colors);
    if (res == EOF) {
        warning_msg("Nepodarilo sa nacitat format suboru\n");
        fclose(f);
        return NULL;
    }

    if (magic_number[0] != 'P' 
            && magic_number[1] != '6' 
            && magic_number[2] != '\0') {
        warning_msg("Nepodporovany format ppm\n");
        fclose(f);
        return NULL;
    }

    struct ppm *ppm= malloc(sizeof(struct ppm) + 3*width*height);
    if (ppm == NULL) {
        warning_msg("Chyba alokacie pamati\n");
        fclose(f);
        return NULL;
    }
    ppm->xsize = width;
    ppm->ysize = height;

    int count = fread(ppm->data, 1, 3 * width * height, f);
    if (count != 3 * width * height) {
        warning_msg("Nepodarilo sa nacitat data zo suboru\n");
        free(ppm);
        fclose(f);
        return NULL;
    }

    fclose(f);
    return ppm;
}

void ppm_free(struct ppm *p) {
    free(p);
}
