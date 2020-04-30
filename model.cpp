#include "model.h"
#include <QStringList>
#include <QDebug>

Model::Model(QObject *parent) :
    QObject(parent)
{
    board = new Board();
    moves = new QList<Move*>();
    currentMove = -1;
}

Model::~Model() {
    delete board;
    delete moves;
}

Move* Model::lastMove() {
    return moves->last();
}

void Model::setBoard(QString b)
{
    board->pieceCount = 0;
    if(!moves->isEmpty()) {
        while(!moves->isEmpty()) {
            if(moves->at(moves->size()-1))
                delete moves->at(moves->size()-1);
            moves->removeAt(moves->size()-1);
        }
    }
    if(b.length() >= 16) {
        for(int i=0; i<SIZE; i++) {
            for(int j=0; j<SIZE; j++) {
                switch(b.at(i*4+j).toAscii()) {
                    case 'P':
                    case 'Q':
                    case 'K':
                    case 'N':
                    case 'R':
                    case 'B':
                        board->pieceCount++;
                        board->board[i][j]->piece = b.at(i*4+j).toAscii();
                    break;
                    case '-':
                        continue;
                    default:
                        //printf("Fehler");
                        return;
                }
            }
        }
        //emit(madeMove());
    }
    qDebug() << "Schlabber";
}

char Model::field(int r, int c)
{
    return board->board[r][c]->piece;
}

void Model::addMove(Move *m) {
    moves->append(m);
    currentMove++;
    //emit(madeMove());
}

Move* Model::undoLastMove() {
    Move *move = moves->at(currentMove);
    move->undoMove(*board);
    currentMove--;
    board->pieceCount++;
    return move;
    //emit(madeMove());
}

void Model::redoMove() {
    if(currentMove < moves->size()) {
        Move *move = moves->at(currentMove+1);
        move->doMove(*board);
        currentMove++;
        board->pieceCount--;
    }
    //emit(madeMove());
}

bool Model::canUndo() {
    return currentMove > 1;
}

bool Model::canRedo() {
    return currentMove + 1 < moves->count();
}

Board *Model::getBoard()
{
    return board;
}

bool Model::makeMove(int rFrom, int cFrom, int rTo, int cTo) {
    Move *m = new Move();
    bool r = m->doMove(*board, rFrom, cFrom, rTo, cTo) != NULL;
    if(r) {
        board->pieceCount--;
        if(currentMove == -1 || currentMove == moves->count()-1) {
            addMove(m);
        } else {
            while(moves->count()-1 > currentMove) {
                moves->removeLast();
            }
            addMove(m);
        }
    } else {
        delete m;
    }
    return r;
}

bool Model::isFinished()
{
    return board->pieceCount == 1;
}

void Model::makeMoves(QString m)
{
    QStringList sl = m.split("#");
    for(int i=0; i<sl.size(); i++) {
        QString element = sl.at(i);
        QStringList l1 = element.split("!");
        QStringList l2 = l1.at(0).split("-");
        QStringList l3 = l1.at(1).split("-");
        makeMove(l2.at(0).toInt(), l2.at(1).toInt(), l3.at(0).toInt(), l3.at(1).toInt());

    }
    //emit(madeMove());
}


