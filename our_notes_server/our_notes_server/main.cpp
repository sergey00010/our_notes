#include <QCoreApplication>

#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server *server = new Server();
    if (!server->listen(QHostAddress::Any, 8282)) {
        qDebug() << "Server could not start!";
        return 1;
    }

    qDebug() << "Server started!";

    return a.exec();
}
