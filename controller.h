#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "model.h"
#include "sccanvas.h"
#include "solver.h"
#include "databasemanager.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    static Controller* getInstance();
    void setSCCanvas(SCCanvas *c);
    void showMainScreen();
    void showSettingsScreen();
    void showAboutScreen();
    void showSelectionScreen();
    void run();
    void pieceDropped();
    void setDraggedItem(QGraphicsPixmapItem *it);
    void saveFinished();
    bool selectNextPuzzle();
    void undoMove();
    void redoMove();
    void saveProgress();
private:
    static Controller* cont;
    SCCanvas *canvas;
    DatabaseManager *dbm;
    int selectedPuzzle;
    QGraphicsPixmapItem *draggedItem;
    Model *model;
    Solver *solver;
    Controller();
    ~Controller();

signals:

public slots:
    void resetPuzzle();
    void undoLastMove();
    void redoLastMove();
    void solveMove();
    void previousPuzzle();
    void nextPuzzle();
    void exitToMenu();


};

#endif // CONTROLLER_H
