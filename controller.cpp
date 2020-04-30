#include "controller.h"
#include "chessboard.h"
#include "move.h"

#include <QDebug>

Controller* Controller::cont;

Controller* Controller::getInstance()
{
    if(cont == NULL) {
        cont = new Controller();
    }
    return cont;
}

void Controller::setSCCanvas(SCCanvas *c)
{
    canvas = c;
}

void Controller::showMainScreen()
{
    canvas->showMainScreen();
}

void Controller::showSettingsScreen()
{
}

void Controller::showAboutScreen()
{
}

void Controller::showSelectionScreen()
{
}

void Controller::run()
{
    bool fin = false;

    if(model) {
        fin = model->isFinished();
    }

    if(selectedPuzzle == -1) {
        dbm->query("Select pk, pnext from puzzles  where completed = 0 order by prev asc, level asc, pk asc");
        selectedPuzzle = dbm->getValue(0).toInt();
    }

    QString qry("select grid, savedmoves from puzzles where z_pk = ");
    qry = qry.append(QString::number(selectedPuzzle).toAscii());
    dbm->query(qry);
    qDebug() << "Brd: " << dbm->getValue(0).toString();
    model->setBoard(dbm->getValue(0).toString());

    //QObject::connect(model, SIGNAL (madeMove()), canvas, SLOT(update()));

    if(dbm->getValue(1).toString() != "") {
        model->makeMoves(dbm->getValue(1).toString());
    }

    qDebug( ) << "Before show";
    canvas->showPuzzle(model, !fin);
    qDebug() << "After show";
    //canvas->update();
}

Controller::Controller()
{
    dbm = new DatabaseManager();
    model = new Model();
    solver = NULL;
    selectedPuzzle = -1;
}

Controller::~Controller()
{
    if(cont != NULL) {
        delete cont;
    }
    if(dbm != NULL) {
        delete dbm;
    }
    if(model != NULL) {
        delete model;
    }
    if(solver != NULL) {
        delete solver;
    }
}

void Controller::resetPuzzle()
{
    run();
}

void Controller::undoLastMove()
{
    canvas->recreatePiece(model->undoLastMove());
    canvas->update();
}

void Controller::redoLastMove()
{
    model->redoMove();
    canvas->update();
}

void Controller::solveMove()
{
     qDebug() << "Solving";
    if(solver == NULL) {
         qDebug() << "Solving 1 ";
        solver = new Solver();
        char brd[SIZE*SIZE+1];

         qDebug() << "Solving 2";
        for(int i=0; i<SIZE; i++) {
            for(int j=0; j<SIZE; j++) {
                brd[i*SIZE+j] = model->getBoard()->board[i][j]->piece == ' ' ? '-' : model->getBoard()->board[i][j]->piece;
            }
        }
         qDebug() << "Solving 3";

        brd[SIZE*SIZE] = '\0';
        qDebug() << "Solving 4";
        qDebug() << brd;
        int sols = solver->initAndRun(brd);
        qDebug() << "After solve";
        if(sols < 1) {
            qDebug() << "sols == 0";
            delete solver;
            solver = NULL;
        }
    }

    if(solver != NULL) {
        qDebug() << "Making move";
        Move * m = solver->getRoot();
        while(m->previous != NULL && m->previous->previous != NULL)
            m = m->previous;
        qDebug() << m->r1 << " " << m->c1 << " " << m->r2 << " " << m->c2;
        bool move = model->makeMove(m->r1, m->c1, m->r2, m->c2);

        if(move) {
            canvas->showPuzzle(model, true);
        }

        delete solver;
        solver = NULL;
    }

}

void Controller::previousPuzzle()
{
    //selectPreviousPuzzle();
}

void Controller::nextPuzzle()
{
    selectNextPuzzle();
    run();
    bool fin = false;

    if(model) {
        fin = model->isFinished();
    }

    if(!fin)
        canvas->oldScene->clear();

}

void Controller::exitToMenu()
{
    saveProgress();
    showMainScreen();
}

void Controller::saveFinished() {
    dbm->query("update puzzles set completed = 1 where pk = " + QString::number(selectedPuzzle));
}

void Controller::saveProgress() {

}

bool Controller::selectNextPuzzle() {
    if(dbm->query("Select pk, pnext from puzzles where prev = " + QString::number(selectedPuzzle) + " and completed = 0 order by level asc, pk asc")) {
        selectedPuzzle = dbm->getValue(0).toInt();
        return true;
    } else {

    }
    return false;
}

void Controller::undoMove() {

}

void Controller::redoMove() {

}

void Controller::setDraggedItem(QGraphicsPixmapItem *it) {
    draggedItem = it;
}

void Controller::pieceDropped()
{
    bool ok = false;
    QList<QGraphicsItem*> c = canvas->scene()->collidingItems(draggedItem);
    if(c.size() > 0) {
        for(int n =0; n<c.size(); n++) {
            bool move = model->makeMove(draggedItem->data(0).toInt(), draggedItem->data(1).toInt(),  c.at(n)->data(0).toInt(), c.at(n)->data(1).toInt());
            if(move) {
                model->lastMove()->movedItem = draggedItem;
                draggedItem->setData(0, c.at(n)->data(0));
                draggedItem->setData(1, c.at(n)->data(1));
                draggedItem->setPos(c.at(n)->data(1).toInt()*90, c.at(n)->data(0).toInt()*90);
                canvas->removeItem(c.at(n));
                if(model->isFinished()) {
                    canvas->removeItem(draggedItem);
                    canvas->removeAllItems();
                    saveFinished();
                    if(selectNextPuzzle()) {
                        run();
                    }
                }
                canvas->update();
                ok = true;
                break;
            }
        }
    } else {

    }
    if(!ok) {
        draggedItem->setPos(draggedItem->data(1).toInt()*90, draggedItem->data(0).toInt()*90);
    }
   // i->setZValue(0);
}
