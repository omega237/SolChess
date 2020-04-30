#ifndef FIELD_H
#define FIELD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Field
{
public:
    Field();
    Field *n, *ne, *e, *se, *s, *sw, *w, *nw;
    int c, r;
    char piece;
};

#endif // FIELD_H
