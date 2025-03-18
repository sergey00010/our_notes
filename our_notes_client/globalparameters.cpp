#include "globalparameters.h"

const QString GlobalParameters::SqlServerAddr  = "127.0.0.1";
const int GlobalParameters::SqlServerPort  = 8383;

const QString GlobalParameters::SqlServerUser  = "root";
const QString GlobalParameters::SqlServerPassword  = "rootpassword";

const QString GlobalParameters::ServerAddr  = "127.0.0.1";
const int GlobalParameters::ServerPort  = 8484;

GlobalParameters::GlobalParameters(QObject *parent)
    : QObject{parent}
{

}
