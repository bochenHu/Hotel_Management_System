#include "sqlservice.h"
#include <QDebug>

sqlService::sqlService()
{

}

bool sqlService::connectToDB(QString dbType, QString hostName, QString dbName, QString userName, QString password, int port, QSqlDatabase &db)
{
    QStringList drivers_available = QSqlDatabase::drivers();
    if (!drivers_available.contains(dbType)){
        qDebug() << "driver is not available here...";
        return false;
    }

    if (QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase(dbType);
    db.setHostName(hostName);
    db.setDatabaseName(dbName);
    db.setUserName(userName);
    db.setPassword(password);
    db.setPort(port);

    return db.open();
}

QList<QList<QString> > sqlService::selectData(QString sqlQuery)
{
    QList<QList<QString>> ret;

    QSqlQuery query(sqlQuery);
    int count = query.record().count();

    while (query.next()) {
        QList<QString> str_list;
        for (int i = 0; i < count; i++){str_list.push_back(query.value(i).toString());}
        ret.push_back(str_list);
    }

    return ret;
}

bool sqlService::operateData(QString Query)
{
    QSqlQuery query;
    query.prepare(Query);

    return query.exec();
}

void sqlService::closeDB(QSqlDatabase db)
{
    db.close();
}
