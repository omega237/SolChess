#ifndef SOLVER_H
#define SOLVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "move.h"

class Solver
{
public:
    Solver();
    int  initAndRun(char* board);
    Move* getRoot() {
        return root;
    }

private:
    int solve(Board &b, Move *move);
    int nSol;
    Move* root;
};

#endif // SOLVER_H
