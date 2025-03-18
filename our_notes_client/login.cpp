#include "login.h"

Login::Login(QObject *parent)
    : QObject{parent}
{
    //connect to server with mysql
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(GlobalParameters::SqlServerAddr);
    db.setPort(GlobalParameters::SqlServerPort);
    db.setUserName(GlobalParameters::SqlServerUser);
    db.setPassword(GlobalParameters::SqlServerPassword);
    create_db();
}

Login::~Login()
{

}

void Login::logIn(QString login, QString password)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "db not open";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = :username");
    query.bindValue(":username", login);

    if (!query.exec()) {
        qDebug() << "error with request:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString storedPassword = query.value(0).toString();
        if (storedPassword == password) {
            qDebug() << "log in ...";
            emit loginSuccess(login);
        } else {
            qDebug() << "wrong password ... ";
            emit error("wrong password ... ");
        }
    } else {
        qDebug() << "User with this login not found ... ";
        emit error("User with this login not found ... ");
    }
}

void Login::create_db()
{
    QString req = "CREATE TABLE users ("
                  "id INT AUTO_INCREMENT PRIMARY KEY,"
                  "username VARCHAR(255) NOT NULL,"
                  "password VARCHAR(255) NOT NULL"
                  ");";
    QString dbName = "notes_db";
    QSqlDatabase db = QSqlDatabase::database();
    WorkWithDb::checkAndCreateDbAndTable(db,dbName,req);
}

int Login::findIdByName(const QString &name)
{

}
