// ppm.h
// Řešení IJC-DU1, příklad b), 28.2.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#ifndef _PPM_H_
#define _PPM_H_

// holds PPM data
struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[]; //RGB bytes, 3*xsize*ysize in total
};

// reads the contents of PPM file
// returns NULL in case of error
struct ppm *ppm_read(const char *filename);

// frees memory dynamically allocated in ppm_read
void ppm_free(struct ppm *p);

#endif
