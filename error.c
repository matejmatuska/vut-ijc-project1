// error.c
// Řešení IJC-DU1, příklad b), 28.2.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "error.h"

void warning_msg(const char *fmt, ...) {
    fprintf(stderr, "CHYBA: ");
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void error_exit(const char *fmt, ...) {
    fprintf(stderr, "CHYBA: ");
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(1);
}
