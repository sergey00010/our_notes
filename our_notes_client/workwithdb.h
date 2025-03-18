#ifndef WORKWITHDB_H
#define WORKWITHDB_H

#include <QObject>
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

class WorkWithDb : public QObject
{
    Q_OBJECT
public:
    explicit WorkWithDb(QObject *parent = nullptr);
    static void checkAndCreateDbAndTable(QSqlDatabase &db, QString &dbName, QString &request);
    static int findIdByName (QSqlDatabase &db, QString &name, QString &tableStringName, QString &tableName);


};

#endif // WORKWITHDB_H
