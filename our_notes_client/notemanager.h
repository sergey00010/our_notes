#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QObject>

#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

#include "noteslistmodel.h"
#include "globalparameters.h"
#include "workwithdb.h"

class NoteManager : public QObject
{
    Q_OBJECT
public:
    explicit NoteManager(QObject *parent = nullptr);
    ~NoteManager();
    //add or edit note
    Q_INVOKABLE void manageNote(int id,const QString name, const QString content, QString usersАccess);
    Q_INVOKABLE void removeNote(int id);
    //load exist notes from database for current user
    Q_INVOKABLE void loadDataFromDb(QString userName);

protected:
    void create_db();
    int findIdByName(const QString &name);

private:
    NotesListModel *noteModel;
    QSqlDatabase db;

};

#endif // NOTEMANAGER_H
