#include "notemanager.h"

NoteManager::NoteManager(QObject *parent)
    : QObject{parent}
{
    //connect to server with mysql
    noteModel = NotesListModel::instance();
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(GlobalParameters::SqlServerAddr);
    db.setPort(GlobalParameters::SqlServerPort);
    db.setUserName(GlobalParameters::SqlServerUser);
    db.setPassword(GlobalParameters::SqlServerPassword);
    create_db();
}

NoteManager::~NoteManager()
{
    db.close();
    delete noteModel;
}

void NoteManager::manageNote(int id, const QString name, const QString content, QString usersАccess)
{
    // -1 is note dont exist, became it need to create
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

        if (!query->exec("SELECT MAX(id) FROM notes"))
            qDebug() << "error with request: " << query->lastError().text();
        else if (query->next())
            noteModel->addNote({query->value(0).toInt(),name,content});

        delete query;
    //edit exist note
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
    QString req = "CREATE TABLE IF NOT EXISTS notes ("
                    "id INT AUTO_INCREMENT PRIMARY KEY, "
                    "noteName VARCHAR(150), "
                    "noteContent TEXT,"
                  "usersAccess TEXT)";
    QString dbName = "notes_db";

    QSqlDatabase db = QSqlDatabase::database();
    WorkWithDb::checkAndCreateDbAndTable(db,dbName,req);
}

int NoteManager::findIdByName(const QString &name) {

}
