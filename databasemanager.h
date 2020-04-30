#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QApplication>
#include <QDir>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlQuery>

class DatabaseManager
    {
    public:
        explicit DatabaseManager();
        ~DatabaseManager();
        bool openDB();
        bool closeDB();
        QSqlError lastError();
        bool query(QString query);
        bool forward();
        QVariant getValue(int col);
private:
        QSqlDatabase db;
        QSqlQuery *q;
    };


#endif // DATABASEMANAGER_H
