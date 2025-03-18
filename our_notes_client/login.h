#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>


class Login : public QObject
{
    Q_OBJECT

public:
    explicit Login(QObject *parent = nullptr);
    ~Login();
    Q_INVOKABLE void logIn(QString login, QString password);

signals:
    void loginSuccess(QString username);
    void error(QString errorcontent);

protected:
    void create_db();
    int findIdByName(const QString &name);

private:
    QSqlDatabase db;



signals:
};

#endif // LOGIN_H
