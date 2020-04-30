#include "solver.h"

Solver::Solver()
{
    nSol = 0;
}

int Solver::solve(Board &b, Move *move) {
    if(b.pieceCount == 1 && nSol == 0) {
        root = move;
        nSol++;
        return 1;
    }
    //if(b.pieceCount == 2) move->printBoard(b);
    for(int r=0; r<SIZE; r++) {
        for(int c=0; c<SIZE; c++) {
            if(b.board[r][c]->piece != ' ') {
                for(int x=0; x<SIZE; x++) {
                    for(int y=0; y<SIZE; y++) {
                        if(b.board[x][y]->piece != ' ' && b.board[r][c] != b.board[x][y]) {
                            Move *m = new Move();
                            if(b.pieceCount > 1 && nSol == 0 && m->doMove(b, r, c, x, y) != NULL) {
                                move->next = m;
                                m->previous = move;
                                b.pieceCount--;
                                solve(b, m);
                                m->undoMove(b);
                                b.pieceCount++;
                            } else {
                                delete m;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int Solver::initAndRun(char* b) {
    Board board;
    root = new Move();
    if(strlen(b) >= 16) {
        for(int i=0; i<SIZE; i++) {
            for(int j=0; j<SIZE; j++) {
                switch(b[i*4+j]) {
                    case 'P':
                    case 'Q':
                    case 'K':
                    case 'N':
                    case 'R':
                    case 'B':
                        board.pieceCount++;
                        board.board[i][j]->piece = b[i*4+j];
                    break;
                    case '-':
                        continue;
                    default:
                        printf("Fehler");
                        return 0;
                }
            }
        }
    }
    nSol = 0;
    solve(board, root);
    return nSol;
}
