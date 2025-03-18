#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QObject>

#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

#include "noteslistmodel.h"

class NoteManager : public QObject
{
    Q_OBJECT
public:
    explicit NoteManager(QObject *parent = nullptr);
    ~NoteManager();
    Q_INVOKABLE void manageNote(int id,const QString name, const QString content, QString usersАccess);
    Q_INVOKABLE void removeNote(int id);
    Q_INVOKABLE void loadDataFromDb(QString userName);

protected:
    void create_db();
    int findIdByName(const QString &name);

private:
    NotesListModel *noteModel;
    QSqlDatabase db;

};

#endif // NOTEMANAGER_H
