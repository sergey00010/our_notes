#ifndef GLOBALPARAMETERS_H
#define GLOBALPARAMETERS_H

#include <QObject>

class GlobalParameters : public QObject
{
    Q_OBJECT
public:
    explicit GlobalParameters(QObject *parent = nullptr);
    static const QString SqlServerAddr;
    static const int SqlServerPort;

    static const QString SqlServerUser;
    static const QString SqlServerPassword;

    static const QString ServerAddr;
    static const int ServerPort;

signals:
};

#endif // GLOBALPARAMETERS_H
