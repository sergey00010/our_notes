#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

#include "globalparameters.h"
#include "workwithdb.h"

/*
This class is used to log in to the user account in the application
*/
class Login : public QObject
{
    Q_OBJECT

public:
    explicit Login(QObject *parent = nullptr);
    ~Login();
    //login to user account
    Q_INVOKABLE void logIn(QString login, QString password);

signals:
    //go to notes on successful login
    void loginSuccess(QString username);
    //error message when login failed
    void error(QString errorcontent);

protected:
    //create a database and table with users on first login
    void create_db();
    int findIdByName(const QString &name);

private:
    QSqlDatabase db;
};

#endif // LOGIN_H
