#include "sccanvas.h"
#include "controller.h"
#include "chessboard.h"
#include "chesspiece.h"

#include <QDesktopWidget>
#include <QObject>
#include <QDebug>
#include <QGraphicsProxyWidget>
#include <QPushButton>

#define min(x, y) (x<=y?x:y)

SCCanvas::SCCanvas(QWidget *parent) :
    QGraphicsView(parent)
{

    brd = NULL;
    setAcceptDrops(true);
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

    itms = new QList<QGraphicsItem*>;

}

SCCanvas::~SCCanvas() {
}

void SCCanvas::showMainScreen()
{
    scene()->clear();

}

void SCCanvas::removeAllItems() {



}

void SCCanvas::showPuzzle(Model *m, bool clearAll = false)
{
    QDesktopWidget desk;
    QRect screenres = desk.screenGeometry(0);
    float w,h;
    w = h = min(screenres.width(), screenres.height())/SIZE;

    if(clearAll) {
        oldScene = scene();
        brd = NULL;
        QGraphicsScene* scene = new QGraphicsScene(0, 0, screenres.width()-1, screenres.height()-1, this);
        setScene(scene);
    }

    if(!brd) {
        QDesktopWidget desk;
        QRect screenres = desk.screenGeometry(0);
        float w,h;
        w = h = min(screenres.width(), screenres.height())/SIZE;

        // add buttons to control area
        QPushButton *btn = new QPushButton();
        btn->setGeometry(0, 4*h+h, w,h/2);
        btn->setText("Reset");
        QGraphicsProxyWidget *btnReset = scene()->addWidget(btn);
        QObject::connect(btn, SIGNAL (clicked()), Controller::getInstance(), SLOT(resetPuzzle()));
        btn = new QPushButton();
        btn->setGeometry(w, 4*h+h, w, h/2);
        btn->setText("Undo");
        QGraphicsProxyWidget *btnUndo = scene()->addWidget(btn);
        QObject::connect(btn, SIGNAL (clicked()), Controller::getInstance(), SLOT(undoLastMove()));
        btn = new QPushButton();
        btn->setGeometry(2*w, 4*h+h, w, h/2);
        btn->setText("Redo");
        QGraphicsProxyWidget *btnRedo = scene()->addWidget(btn);
        QObject::connect(btn, SIGNAL (clicked()), Controller::getInstance(), SLOT(redoLastMove()));
        btn = new QPushButton();
        btn->setGeometry(3*w, 4*h+h, w, h/2);
        btn->setText("Solve");
        QGraphicsProxyWidget *btnSolve = scene()->addWidget(btn);
        QObject::connect(btn, SIGNAL (clicked()), Controller::getInstance(), SLOT(solveMove()));
        btn = new QPushButton();
        btn->setGeometry(0, 5*h+h, w, h/2);
        btn->setText("Previous");
        QGraphicsProxyWidget *btnPrev = scene()->addWidget(btn);
        QObject::connect(btn, SIGNAL (clicked()), Controller::getInstance(), SLOT(previousPuzzle()));
        btn = new QPushButton();
        btn->setGeometry(w, 5*h+h, w, h/2);
        btn->setText("Next");
        QGraphicsProxyWidget *btnNext = scene()->addWidget(btn);
        QObject::connect(btn, SIGNAL (clicked()), Controller::getInstance(), SLOT(nextPuzzle()));
        btn = new QPushButton();
        btn->setGeometry(3*w, 5*h+h, w, h/2);
        btn->setText("Menu");
        QGraphicsProxyWidget *btnMenu = scene()->addWidget(btn);
        QObject::connect(btn, SIGNAL (clicked()), Controller::getInstance(), SLOT(exitToMenu()));

    }

    bool filled = true;
    QGraphicsScene *s = scene();
    QGraphicsRectItem *b = new QGraphicsRectItem(NULL, s);
    b->setRect(0, 0, w, h);
    b->setFlag(QGraphicsItem::ItemIsPanel);

    brd = b;

    qDebug() << "Building pieces";

    for(int i=0; i<SIZE; i++) {
        filled = !filled;
        for(int j=0; j<SIZE; j++) {
            QGraphicsRectItem *it = new QGraphicsRectItem(j*w, i*h, w+1, h+1, b);
            it->setBrush(filled? Qt::blue : Qt::white);
            filled = !filled;
            if(m->field(i,j) != 32) {
                //qDebug() << m->field(i,j) << " " << j*w << " " << i*h;
                ChessPiece *cp = new ChessPiece(m->field(i,j));
                cp->setPosition(j*w, i*h);
                cp->setData(0, i);
                cp->setData(1, j);
                s->addItem(cp);
                //itms->append(cp);
            } else {
                //qDebug() << m->field(i,j) << " ";
            }
        }
    }

    qDebug() << "Boom";

}

QGraphicsItem* SCCanvas::getActiveItem()
{
    return scene()->focusItem();
}

QList<QGraphicsItem*> SCCanvas::getCollisionItem(QGraphicsItem* i)
{
    return scene()->collidingItems(i);
}

void SCCanvas::removeItem(QGraphicsItem *i) {
    i->hide();
    scene()->removeItem(i);
}

void SCCanvas::recreatePiece(Move *m) {
    QDesktopWidget desk;
    QRect screenres = desk.screenGeometry(0);
    float w,h;
    w = h = min(screenres.width(), screenres.height())/SIZE;

    ChessPiece *cp = new ChessPiece(m->captured);
    cp->setPosition(m->c2*w, m->r2*h);
    cp->setData(0, m->r2);
    cp->setData(1, m->c2);
    scene()->addItem(cp);

    ((ChessPiece*)m->movedItem)->setPosition(m->c1*w, m->r1*h);

}

void SCCanvas::update()
{
    QGraphicsView::update();
}
