#include "chesspiece.h"
#include "chessboard.h"
#include "controller.h"

#include <QDesktopWidget>
#include <QBitmap>
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>
#include <QPointF>

#define min(x, y) (x<=y?x:y)

ChessPiece::ChessPiece(char type)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsPanel);
    QPixmap k(":/King_1_082.gif");
    QPixmap q(":/Queen_1_082.gif");
    QPixmap b(":/Bishop_1_082.gif");
    QPixmap n(":/Knight_1_082.gif");
    QPixmap r(":/Rook_1_082.gif");
    QPixmap p(":/Pawn_1_082.gif");
    switch(type) {
    case BLACK_KING:
    case WHITE_KING:
        k.setMask(k.createHeuristicMask());
        setPixmap(k);
        break;
    case BLACK_QUEEN:
    case WHITE_QUEEN:
        q.setMask(q.createHeuristicMask());
        setPixmap(q);
        break;
    case BLACK_BISHOP:
    case WHITE_BISHOP:
        b.setMask(b.createHeuristicMask());
        setPixmap(b);
        break;
    case BLACK_NIGHT:
    case WHITE_NIGHT:
        n.setMask(n.createHeuristicMask());
        setPixmap(n);
        break;
    case BLACK_ROOK:
    case WHITE_ROOK:
        r.setMask(r.createHeuristicMask());
        setPixmap(r);
        break;
    case BLACK_PAWN:
    case WHITE_PAWN:
        p.setMask(p.createHeuristicMask());
        setPixmap(p);
        break;
    default:
        qDebug() << "There is not item type : " << type;
    }

}

void ChessPiece::setPosition(int leftPos, int topPos)
{
    l = leftPos;
    t = topPos;
    setPos(l, t);
}

void ChessPiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if(dragged) {
        dragged = false;
        Controller::getInstance()->pieceDropped();
        setZValue(0);
    }
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

void ChessPiece::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    dragged = true;
    Controller::getInstance()->setDraggedItem(this);
    setZValue(0.5);
    QGraphicsPixmapItem::mouseMoveEvent(event);
}

QRectF ChessPiece::boundingRect() const
{
    QDesktopWidget desk;
    QRect screenres = desk.screenGeometry(0);
    float w,h;
    w = h = min(screenres.width(), screenres.height())/SIZE;
    QRect r(0, 0, w, h);
    QRectF br(r);
    return br;
}

void ChessPiece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QDesktopWidget desk;
    QRect screenres = desk.screenGeometry(0);
    float w,h;
    w = h = min(screenres.width(), screenres.height())/SIZE;
    painter->drawPixmap(boundingRect().x(), boundingRect().y(), w, h, pixmap());
}
