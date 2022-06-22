#ifndef SQLSERVICE_H
#define SQLSERVICE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QList>

class sqlService: public QObject
{
protected:
    sqlService();
    static bool connectToDB(QString dbType, QString hostName, QString dbName,
                            QString userName, QString password, int port, QSqlDatabase& db);
    static QList<QList<QString>> selectData(QString sqlQuery);
    static bool operateData(QString Query);
    static void closeDB(QSqlDatabase db);
};

#endif // SQLSERVICE_H
