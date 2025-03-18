#include "login.h"

Login::Login(QObject *parent)
    : QObject{parent}
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(8383);
    db.setUserName("root");
    db.setPassword("rootpassword");

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
    if (!db.open()) {
        qDebug() << "error connection to MySQL:" << db.lastError().text();
    }

    QSqlQuery query(db);
    if (!query.exec("CREATE DATABASE IF NOT EXISTS notes_db")) {
        qDebug() << "error create db:" << query.lastError().text();
        db.close();
    }

    db.close();
    db.setDatabaseName("notes_db");
    if (!db.open()) {
        qDebug() << "error connect to 'notes_db':" << db.lastError().text();
    }

    if (!query.exec("CREATE TABLE users ("
            "id INT AUTO_INCREMENT PRIMARY KEY,"
            "username VARCHAR(255) NOT NULL,"
            "password VARCHAR(255) NOT NULL"
            ");")) {
        qDebug() << "error create table 'users':" << query.lastError().text();
        db.close();
    }
}

int Login::findIdByName(const QString &name)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return -1;
    }

    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT id FROM notes WHERE noteName = :name");
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
