#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "client.h"
#include "notemanager.h"
#include "noteslistmodel.h"
#include "login.h"
#include "globalparameters.h"

/*
created bu Sergey Kuzmenko
note taking app
*/

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/our_notes_client/main.qml"));

    GlobalParameters gl;

    client *clientapp = new client();

    NotesListModel *noteModel = NotesListModel::instance();

    qmlRegisterType<NotesListModel>("Custom", 1, 0, "NoteModel");
    engine.rootContext()->setContextProperty("noteModel", noteModel);

    NoteManager *noteManager = new NoteManager();
    engine.rootContext()->setContextProperty("noteManager", noteManager);

    Login *login = new Login();
    engine.rootContext()->setContextProperty("login", login);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
