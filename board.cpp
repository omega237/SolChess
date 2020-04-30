#include "board.h"

Board::Board()
{
    pieceCount=0;
    offboard = new Field();
    offboard->n = offboard->ne = offboard->nw = offboard->e = offboard->s = offboard->se = offboard->sw = offboard->w = offboard;
    for(int r=0; r<SIZE; r++) {
        for(int c=0; c<SIZE; c++) {
            board[r][c] = new Field();
            board[r][c]->piece = ' ';
            board[r][c]->n = board[r][c]->ne = board[r][c]->e = board[r][c]->se = board[r][c]->s = board[r][c]->sw = board[r][c]->w = board[r][c]->nw = offboard;
            board[r][c]->r = r;
            board[r][c]->c = c;
        }
    }
    for(int x=0; x<SIZE; x++) {
        for(int y=0; y<SIZE; y++) {
            board[x][y]->n = x == 0 ? offboard : board[x-1][y];
            board[x][y]->ne = (x == 0 || y == SIZE-1) ? offboard : board[x-1][y+1];
            board[x][y]->e = y == SIZE-1 ? offboard : board[x][y+1];
            board[x][y]->se = (y == SIZE-1 || x == SIZE-1) ? offboard : board[x+1][y+1];
            board[x][y]->s = x == SIZE-1 ? offboard : board[x+1][y];
            board[x][y]->sw = (y == 0 || x == SIZE-1) ? offboard : board[x+1][y-1];
            board[x][y]->w = y == 0 ? offboard : board[x][y-1];
            board[x][y]->nw = (y == 0 || x == 0) ? offboard : board[x-1][y-1];
        }
    }
}

Board::~Board() {
    for(int r=0; r<SIZE; r++) {
        for(int c=0; c<SIZE; c++) {
            delete board[r][c];
        }
    }
}
