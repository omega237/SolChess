#ifndef MOVE_H
#define MOVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QGraphicsPixmapItem>
#include "board.h"

class Move
{
public:
    Move();
    void printBoard(Board &board);
    Move* doMove(Board &b, int rFrom, int cFrom, int rTo, int cTo);
    void doMove(Board &b);
    void undoMove(Board &b);
    int r1, c1, r2, c2, sc;
    char captured;
    Move *previous, *next, *sibling;
    QGraphicsPixmapItem *movedItem;
};

#endif // MOVE_H
