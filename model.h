#ifndef MODEL_H
#define MODEL_H

#include "board.h"
#include "move.h"
#include <QObject>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);
    void setBoard(QString b);
    void makeMoves(QString m);
    char field(int r, int c);
    Board *getBoard();
    ~Model();
    bool makeMove(int rFrom, int cFrom, int rTo, int cTo);
    bool isFinished();
    Move *undoLastMove();
    void redoMove();
    bool canUndo();
    bool canRedo();
    Move *lastMove();
private:
    Board *board;
    QList<Move*> *moves;
    int currentMove;
    void addMove(Move *m);
signals:
    void madeMove();
public slots:
};

#endif // MODEL_H
