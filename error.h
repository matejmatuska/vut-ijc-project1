// error.h
// Řešení IJC-DU1, příklad b), 28.2.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#ifndef _ERROR_H_
#define _ERROR_H_

// prints "CHYBA: " and message according to fmt
void warning_msg(const char *fmt, ...);

// same as warning_msg but also exits with exit code 1
void error_exit(const char *fmt, ...);

#endif
