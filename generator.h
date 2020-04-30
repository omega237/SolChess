#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solver.h"

typedef unsigned long marker;
static const char set[33] = "KQRRNNBBPPPPPPPP----------------";

class Generator
{
public:
    Generator();
    char* generate();
private:
    void comb(int pool, int need, marker chosen, int at);

    marker one;
    char b[17];
    bool run;
};

#endif // GENERATOR_H
