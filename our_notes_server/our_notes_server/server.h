#ifndef SERVER_H
#define SERVER_H


#include <QtCore/QCoreApplication>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QDebug>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // SERVER_H
