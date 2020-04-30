#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "field.h"
#define SIZE 4

class Board
{
public:
    Board();
    ~Board();
    Field *board[SIZE][SIZE];
    Field *offboard;
    int pieceCount;
};

#endif // BOARD_H
