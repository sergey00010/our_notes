#ifndef CLIENT_H
#define CLIENT_H


#include <QtCore/QCoreApplication>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QDebug>
#include <QObject>

#include "globalparameters.h"

class client : public QObject
{
    Q_OBJECT
public:
    client();
    ~client();
    void connectToServer();
private:
    QTcpSocket socket;
};

#endif // CLIENT_H
