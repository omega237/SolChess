#include "mainwindow.h"

#include <QtGui/QApplication>
#include <QDir>
#include <QVariant>



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "controller.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    MainWindow mainWindow;
    /*mainWindow.setOrientation(MainWindow::ScreenOrientationLockPortrait);
    mainWindow.showExpanded();*/
    mainWindow.showFullScreen();

    return app.exec();
}
