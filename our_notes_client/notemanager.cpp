#include "notemanager.h"

NoteManager::NoteManager(QObject *parent)
    : QObject{parent}
{
    noteModel = NotesListModel::instance();
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(8383);
    db.setUserName("root");
    db.setPassword("rootpassword");

    create_db();
}

NoteManager::~NoteManager()
{
    db.close();
    delete noteModel;
}

void NoteManager::manageNote(int id, const QString name, const QString content, QString usersАccess)
{
    if(id == -1){
        db.transaction();

        QSqlQuery *query = new QSqlQuery();
        query->prepare("INSERT INTO notes (noteName, noteContent, usersAccess) VALUES (:name, :content, :usersAccess)");
        query->bindValue(":name", name);
        query->bindValue(":content", content);
        query->bindValue(":usersAccess", usersАccess);

        if (!query->exec()) {
            qDebug() << "Failed to insert note:" << query->lastError().text();
            db.rollback();
        }

        db.commit();
        qDebug() << "Note added successfully!";

        if (!query->exec("SELECT MAX(id) FROM notes")) {
            qDebug() << "error with request: " << query->lastError().text();
        }
        else if (query->next()) {
            noteModel->addNote({query->value(0).toInt(),name,content});
        }

        delete query;
    }else{

        db.transaction();

        QSqlQuery *query = new QSqlQuery();
        query->prepare("UPDATE notes SET noteName = :newName, noteContent = :newContent WHERE id = :noteId");
        query->bindValue(":newName", name);
        query->bindValue(":newContent", content);
        query->bindValue(":noteId", id);

        if (!query->exec()) {
            qDebug() << "Failed to update note:" << query->lastError().text();
            db.rollback();
        } else {
            db.commit();
            qDebug() << "Note updated successfully!";
        }

        delete query;

        noteModel->updateNote(id,name,content);
    }
}

void NoteManager::removeNote(int id)
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("DELETE FROM notes WHERE id = :id");
    query->bindValue(":id", id);

    if (!query->exec()) {
        qDebug() << "error delete note: " << query->lastError().text();
    }
    noteModel->removeNote(id);
    delete query;
}

void NoteManager::loadDataFromDb(QString userName)
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT * FROM notes WHERE usersAccess = :usersAccess");
    query->bindValue(":usersAccess", userName);


    if (!query->exec()) {
        qDebug() << "error with request: " << query->lastError().text();
        return;
    }

    while (query->next()) {
        int id = query->value("id").toInt();
        QString name = query->value("noteName").toString();
        QString content = query->value("noteContent").toString();
        noteModel->addNote({id,name,content});
    }

    delete query;
}

void NoteManager::create_db()
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

    if (!query.exec("CREATE TABLE IF NOT EXISTS notes ("
                    "id INT AUTO_INCREMENT PRIMARY KEY, "
                    "noteName VARCHAR(150), "
                    "noteContent TEXT,"
                    "usersAccess TEXT)")) {
        qDebug() << "error create table 'notes':" << query.lastError().text();
        db.close();
    }
}

int NoteManager::findIdByName(const QString &name) {
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
