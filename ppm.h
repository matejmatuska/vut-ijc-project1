#ifndef _PPM_H_
#define _PPM_H_

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
