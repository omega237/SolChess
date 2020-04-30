#ifndef SCCANVAS_H
#define SCCANVAS_H

#include <QGraphicsView>

#include "model.h"


class SCCanvas : public QGraphicsView
{
    Q_OBJECT
public:

    explicit SCCanvas(QWidget *parent = 0);
    ~SCCanvas();
    void showMainScreen();
    void showPuzzle(Model *m, bool clearAll);

    QGraphicsRectItem *brd;
    QGraphicsItem *getActiveItem();
    QList<QGraphicsItem *> getCollisionItem(QGraphicsItem *i);
    void removeItem(QGraphicsItem *i);

    void recreatePiece(Move *m);
    void removeAllItems();

     QGraphicsScene * oldScene;
protected:


private:
    //QPixmap *king, *queen, *rook, *bishop, *knight, *pawn;
    QList<QGraphicsItem*> *itms;

signals:
    
public slots:
    void update();
    
};

#endif // SCCANVAS_H
