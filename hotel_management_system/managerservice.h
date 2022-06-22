#ifndef MANAGERSERVICE_H
#define MANAGERSERVICE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QList>
#include "manager.h"
#include "sqlservice.h"

class managerService : public sqlService
{
private:
    managerService();
    static manager parseQStr(QList<QString> strList);
    static QString getInsertQuery(QString managerID, QString hotelID, QString managerPwd, QString managerName, QString phoneNum, QString managerAddress);
    static QString getSelectMaxManagerIDQuery(QString hotelID);

    static bool exec_query(QString query);
public:
    static QList<manager> selectManagerByID(QString managerID);
    static QList<manager> selectAllManagers(QString query = "SELECT * FROM manager");
    static bool InsertManager(QString managerID, QString hotelID, QString managerPwd, QString managerName, QString phoneNum, QString managerAddress);
    static QString selectMaxManagerIdByHotelId(QString hotelID);
    static bool DeleteAll(QString query = "DELETE FROM manager");
    static bool DeleteByManagerID(QString ManagerID);
    static bool UpdateByManagerID(QString ManagerID, QString hotelID, QString managerPwd,
                                  QString managerName, QString phoneNum, QString managerAddress);
};

#endif // MANAGERSERVICE_H
