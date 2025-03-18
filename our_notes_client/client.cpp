#include "client.h"

client::client() : socket(0) {
    connectToServer();
}

client::~client()
{
    socket.disconnectFromHost();
}

void client::connectToServer()
{
    socket.connectToHost("127.0.0.1", 8282);

    if (socket.waitForConnected()) {
        qDebug() << "Connected to server!";

        QByteArray message = "Hello, Server!";
        socket.write(message);
        socket.waitForBytesWritten();

        if (socket.waitForReadyRead()) {
            QByteArray response = socket.readAll();
            qDebug() << "Received:" << response;
        }
    } else {
        qDebug() << "Could not connect to server!";
    }
}
