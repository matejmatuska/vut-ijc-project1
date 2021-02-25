#include <stdio.h>
#include <stdlib.h>

#include "bitset.h"
#include "eratosthenes.h"

#define N 200000000 // 200 milion

int main() {

    bitset_create(pole, 100);

    Eratosthenes(pole);

    //bitset_free(pole);

    return 0;
}
