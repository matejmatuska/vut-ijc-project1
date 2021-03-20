// eratosthenes.h
// Řešení IJC-DU1, příklad a), 28.2.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#ifndef _ERATOSTHENES_H_
#define _ERATOSTHENES_H_

#include "bitset.h"

// The sieve of Eratostenes
// after this function returns bits in bitset "pole"
// at prime indices are set to 0, otherwise 1
void Eratosthenes(bitset_t pole);

#endif
