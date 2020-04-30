#include "move.h"

Move::Move()
{
    previous = next = sibling = NULL;
    r1 = c1 = r2 = c2 = sc = 0;
    captured = ' ';
}

void Move::printBoard(Board &board) {
    for(int a=0; a<SIZE; a++) {
        for(int b=0; b<SIZE; b++) {
            printf("%c|", board.board[a][b]->piece);
        }
        printf("\n");
    }
    printf("\n");
}

Move* Move::doMove(Board &b, int rFrom, int cFrom, int rTo, int cTo) {
    r1 = rFrom;
    c1 = cFrom;
    r2 = rTo;
    c2 = cTo;
    //printf("Target content: %c\n", b.board[rTo][cTo]->piece);
    captured = b.board[rTo][cTo]->piece;
    if(captured == ' ') {
        return NULL;
    }
    switch(b.board[rFrom][cFrom]->piece) {
        case 'P':
            if(rTo >= 0 && rTo == rFrom-1 && cTo >= 0 && cTo < SIZE) {
                Field *target = NULL;
                if(b.board[rFrom][cFrom]->ne->c == cTo) {
                    target = b.board[rFrom][cFrom]->ne;
                } else if(b.board[rFrom][cFrom]->nw->c == cTo) {
                    target = b.board[rFrom][cFrom]->nw;
                } else if(b.board[rFrom][cFrom]->n->c == cTo && b.board[rFrom][cFrom]->n->piece == ' ') {
                    target = b.board[rFrom][cFrom]->n;
                }
                if(target != NULL) {
                    target->piece = b.board[rFrom][cFrom]->piece;
                    b.board[rFrom][cFrom]->piece = ' ';
                    return this;
                }
                return NULL;
            }
            break;
        case 'N':
            if(rTo >= 0 && rTo < SIZE && cTo >= 0 && cTo < SIZE) {
                Field *target = NULL;
                if(b.board[rFrom][cFrom]->n->n->e->c == cTo && b.board[rFrom][cFrom]->n->n->e->r == rTo) {
                    target = b.board[rFrom][cFrom]->n->n->e;
                } else if(b.board[rFrom][cFrom]->n->e->e->c == cTo && b.board[rFrom][cFrom]->n->e->e->r == rTo) {
                    target = b.board[rFrom][cFrom]->n->e->e;
                } else if(b.board[rFrom][cFrom]->n->w->w->c == cTo && b.board[rFrom][cFrom]->n->w->w->r == rTo) {
                    target = b.board[rFrom][cFrom]->n->w->w;
                } else if(b.board[rFrom][cFrom]->n->n->w->c == cTo && b.board[rFrom][cFrom]->n->n->w->r == rTo) {
                    target = b.board[rFrom][cFrom]->n->n->w;
                } else if(b.board[rFrom][cFrom]->w->w->n->c == cTo && b.board[rFrom][cFrom]->w->w->n->r == rTo) {
                    target = b.board[rFrom][cFrom]->w->w->n;
                } else if(b.board[rFrom][cFrom]->w->w->s->c == cTo && b.board[rFrom][cFrom]->w->w->s->r == rTo) {
                    target = b.board[rFrom][cFrom]->w->w->s;
                } else if(b.board[rFrom][cFrom]->s->s->e->c == cTo && b.board[rFrom][cFrom]->s->s->e->r == rTo) {
                    target = b.board[rFrom][cFrom]->s->s->e;
                } else if(b.board[rFrom][cFrom]->s->s->w->c == cTo && b.board[rFrom][cFrom]->s->s->w->r == rTo) {
                    target = b.board[rFrom][cFrom]->s->s->w;
                } else if(b.board[rFrom][cFrom]->w->w->s->c == cTo && b.board[rFrom][cFrom]->w->w->s->r == rTo) {
                    target = b.board[rFrom][cFrom]->w->w->s;
                } else if(b.board[rFrom][cFrom]->w->w->n->c == cTo && b.board[rFrom][cFrom]->w->w->n->r == rTo) {
                    target = b.board[rFrom][cFrom]->w->w->n;
                } else if(b.board[rFrom][cFrom]->s->e->e->c == cTo && b.board[rFrom][cFrom]->s->e->e->r == rTo) {
                    target = b.board[rFrom][cFrom]->s->e->e;
                } else if(b.board[rFrom][cFrom]->s->w->w->c == cTo && b.board[rFrom][cFrom]->s->w->w->r == rTo) {
                    target = b.board[rFrom][cFrom]->s->w->w;
                }
                if(target != NULL) {
                    target->piece = b.board[rFrom][cFrom]->piece;
                    b.board[rFrom][cFrom]->piece = ' ';
                    return this;
                }
                return NULL;
            }
            break;
        case 'Q':
            if(rTo >= 0 && rTo < SIZE && cTo >= 0 && cTo < SIZE) {
                Field *target = NULL;
                target = b.board[rFrom][cFrom];
                if(rTo > rFrom && cTo > cFrom) {
                    while(target->se != b.board[rTo][cTo]) {
                        target = target->se;
                        if(target  == b.offboard|| target->piece != ' ') {
                            return NULL;
                        }
                    }
                } else if(rTo > rFrom && cTo == cFrom) {
                    while(target->s != b.board[rTo][cTo]) {
                        target = target->s;
                        if(target  == b.offboard || target->piece != ' ') {
                            return NULL;
                        }
                    }
                } else if(rTo == rFrom && cTo > cFrom) {
                    while(target->e != b.board[rTo][cTo]) {
                        target = target->e;
                        if(target  == b.offboard || target->piece != ' ') {
                            return NULL;
                        }
                    }
                } else if(rTo < rFrom && cTo == cFrom) {
                    while(target->n != b.board[rTo][cTo]) {
                        target = target->n;
                        if(target  == b.offboard || target->piece != ' ') {
                            return NULL;
                        }
                    }
                } else if(rTo > rFrom && cTo < cFrom) {
                    while(target->sw != b.board[rTo][cTo]) {
                        target = target->sw;
                        if(target  == b.offboard || target->piece != ' ') {
                            return NULL;
                        }

                    }
                } else if(rTo == rFrom && cTo < cFrom) {
                    while(target->w != b.board[rTo][cTo]) {
                        target = target->w;
                        if(target  == b.offboard || target->piece != ' ') {
                            return NULL;
                        }
                    }
                } else if(rTo < rFrom && cTo < cFrom) {
                    while(target->nw != b.board[rTo][cTo]) {
                        target = target->nw;
                        if(target  == b.offboard || target->piece != ' ') {
                            return NULL;
                        }
                    }
                } else if(rTo < rFrom && cTo > cFrom) {
                    while(target->ne != b.board[rTo][cTo]) {
                        target = target->ne;
                        if(target  == b.offboard || target->piece != ' ') {
                            return NULL;
                        }
                    }
                }
                target = b.board[rTo][cTo];
                target->piece = b.board[rFrom][cFrom]->piece;
                b.board[rFrom][cFrom]->piece = ' ';
                return this;
            }
            break;
        case 'B':
            if(rTo >= 0 && rTo < SIZE && cTo >= 0 && cTo < SIZE) {
                Field *target = NULL;
                target = b.board[rFrom][cFrom];
                if(rTo > rFrom && cTo > cFrom) {
                    while(target->se != b.board[rTo][cTo]) {
                        target = target->se;
                        if(target  == b.offboard || target->piece != ' ') {
                            return NULL;
                        }
                    }
                } else if(rTo > rFrom && cTo < cFrom) {
                    while(target->sw != b.board[rTo][cTo]) {
                        target = target->sw;
                        if(target  == b.offboard || target->piece != ' ') {
                            return NULL;
                        }

                    }
                } else if(rTo < rFrom && cTo < cFrom) {
                    while(target->nw != b.board[rTo][cTo]) {
                        target = target->nw;
                        if(target  == b.offboard || target->piece != ' ') {
                            return NULL;
                        }
                    }
                } else if(rTo < rFrom && cTo > cFrom) {
                    while(target->ne != b.board[rTo][cTo]) {
                        target = target->ne;
                        if(target  == b.offboard || target->piece != ' ') {
                            return NULL;
                        }
                    }
                } else {
                    return NULL;
                }
                target = b.board[rTo][cTo];
                target->piece = b.board[rFrom][cFrom]->piece;
                b.board[rFrom][cFrom]->piece = ' ';
                return this;
            }
            break;
        case 'R':
            if(rTo >= 0 && rTo < SIZE && cTo >= 0 && cTo < SIZE) {
                Field *target = NULL;
                target = b.board[rFrom][cFrom];
                if(rTo > rFrom && cTo == cFrom) {
                    while(target->s != b.board[rTo][cTo]) {
                        target = target->s;
                        if(target  == b.offboard || target->piece != ' ') {
                            return NULL;
                        }
                    }
                } else if(rTo == rFrom && cTo > cFrom) {
                    while(target->e != b.board[rTo][cTo]) {
                        target = target->e;
                        if(target  == b.offboard || target->piece != ' ') {
                            return NULL;
                        }
                    }
                } else if(rTo < rFrom && cTo == cFrom) {
                    while(target->n != b.board[rTo][cTo]) {
                        target = target->n;
                        if(target  == b.offboard || target->piece != ' ') {
                            return NULL;
                        }
                    }
                } else if(rTo == rFrom && cTo < cFrom) {
                    while(target->w != b.board[rTo][cTo]) {
                        target = target->w;
                        if(target  == b.offboard || target->piece != ' ') {
                            return NULL;
                        }
                    }
                } else {
                    return NULL;
                }
                target = b.board[rTo][cTo];
                target->piece = b.board[rFrom][cFrom]->piece;
                b.board[rFrom][cFrom]->piece = ' ';
                return this;
            }
            break;
        case 'K':
            if(rTo >= 0 && rTo < SIZE && cTo >= 0 && cTo < SIZE) {
                Field *target = NULL;
                target = b.board[rTo][cTo];
                if(target != NULL && (target->ne == b.board[rFrom][cFrom] || target->e == b.board[rFrom][cFrom] || target->se == b.board[rFrom][cFrom] || target->s == b.board[rFrom][cFrom] || target->sw == b.board[rFrom][cFrom] || target->w == b.board[rFrom][cFrom] || target->nw == b.board[rFrom][cFrom] || target->n == b.board[rFrom][cFrom])) {
                    target->piece = b.board[rFrom][cFrom]->piece;
                    b.board[rFrom][cFrom]->piece = ' ';
                    return this;
                }
                return NULL;

            }
            break;
        default:
            return NULL;
    }
    return NULL;
}

void Move::doMove(Board &b)
{
    doMove(b, r1, c1, r2, c2);
}

void Move::undoMove(Board &b) {
     b.board[r1][c1]->piece = b.board[r2][c2]->piece;
     b.board[r2][c2]->piece = captured;
}
