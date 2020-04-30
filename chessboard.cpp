#include "chessboard.h"

#define min(x, y) (x<=y?x:y)

#include <QDesktopWidget>

ChessBoard::ChessBoard(QGraphicsRectItem *parent) :
    QGraphicsRectItem(parent)
{
    setFlag(QGraphicsItem::ItemIsPanel);
}

QRectF ChessBoard::boundingRect() const {
    return rect();
}

void ChessBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawRect(rect().x(), rect().y(), rect().height()-1, rect().width()-1);
}
