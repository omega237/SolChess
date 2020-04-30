#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "chessboard.h"

class ChessPiece :  public QGraphicsPixmapItem
{
public:
    explicit ChessPiece(char type);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    
    static const char BLACK_PAWN = 'p';
    static const char BLACK_ROOK = 'r';
    static const char BLACK_NIGHT = 'n';
    static const char BLACK_BISHOP = 'b';
    static const char BLACK_QUEEN = 'q';
    static const char BLACK_KING = 'k';
    static const char WHITE_PAWN = 'P';
    static const char WHITE_ROOK = 'R';
    static const char WHITE_NIGHT = 'N';
    static const char WHITE_BISHOP = 'B';
    static const char WHITE_QUEEN = 'Q';
    static const char WHITE_KING = 'K';


    void setPosition(int leftPos, int topPos);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    int l, t;
    bool dragged;

    
};

#endif // CHESSPIECE_H
