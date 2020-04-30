#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "board.h"
#include <QObject>
#include <QGraphicsRectItem>
#include <QPainter>

class ChessBoard : public QGraphicsRectItem
{
public:
    explicit ChessBoard(QGraphicsRectItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // CHESSBOARD_H
