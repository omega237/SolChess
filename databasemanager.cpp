#include "databasemanager.h"
#include <QDebug>

DatabaseManager::DatabaseManager() {
    q = NULL;
    openDB();
    qDebug() << lastError().text();
}

DatabaseManager::~DatabaseManager() {
    closeDB();
}

bool DatabaseManager::openDB() {
    // look for puzzle database

    QString path(QDir::separator());
    path.append("opt");
    path.append(QDir::separator()).append("SolitaireChess");
    path.append(QDir::separator()).append("SolChess.db");
    path = QDir::toNativeSeparators(path);

    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName(QDir::toNativeSeparators(QApplication::applicationDirPath().append(QDir::separator()).append("SolChess.db")));
    db.setDatabaseName(path);
    return db.open();
}

QSqlError DatabaseManager::lastError() {
    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
}

bool DatabaseManager::closeDB() {
    // Close database
    if(q != NULL) {
        delete q;
    }
    db.close();
    return true;
}

bool DatabaseManager::query(QString query) {
    if(q != NULL) {
        delete q;
    }
    q = new QSqlQuery(query, db);
    q->exec();
    return q->next();
}

bool DatabaseManager::forward() {
    return q->next();
}

QVariant DatabaseManager::getValue(int col) {
    if(q == NULL) {
        return NULL;
    }
    return q->value(col);
}
