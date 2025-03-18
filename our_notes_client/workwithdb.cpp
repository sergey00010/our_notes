#include "workwithdb.h"

WorkWithDb::WorkWithDb(QObject *parent)
    : QObject{parent}
{}

void WorkWithDb::checkAndCreateDbAndTable(QSqlDatabase &db, QString &dbName, QString &request)
{
    if (!db.open())
        qDebug() << "error connection to MySQL:" << db.lastError().text();

    QSqlQuery *query = new QSqlQuery(db);
    QString reqDb = "CREATE DATABASE IF NOT EXISTS " + dbName;
    if (!query->exec(reqDb)) {
        qDebug() << "error create db:" << query->lastError().text();
        db.close();
    }

    db.close();

    db.setDatabaseName(dbName);
    if (!db.open())
        qDebug() << "error connect to "<<dbName<<": "<< db.lastError().text();
    if (!query->exec(request)) {
        qDebug() << "error create table "<< query->lastError().text();
        db.close();
    }
    delete query;
}

int WorkWithDb::findIdByName(QSqlDatabase &db, QString &name, QString &tableStringName, QString &tableName)
{
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return -1;
    }

    QSqlQuery *query = new QSqlQuery();
    query->prepare(QString::fromUtf8("SELECT id FROM notes WHERE %1 = :name").arg("tableStringName"));
    query->bindValue(":name", name);

    if (!query->exec()) {
        qDebug() << "Failed to execute query:" << query->lastError().text();
        delete query;
        return -1;
    }

    if (query->next()) {
        int id = query->value(0).toInt();
        delete query;
        return id;
    } else {
        qDebug() << "No record found with name:" << name;
        delete query;
        return -1;
    }
    delete query;
}
