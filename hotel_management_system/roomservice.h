#ifndef ROOMSERVICE_H
#define ROOMSERVICE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QList>

#include "room.h"
#include "sqlservice.h"


class roomService: public sqlService
{
protected:
    roomService();
    static room parseQStr(QList<QString> strList);
    static QString getQueryByManagerID(QString ManagerID);
    static QString getUpdateQuery(QString roomID, QString checkInDate, QString checkOutDate);
    static QString getUpdateRoomQuery(QString roomID);
    static QString getUpdateRoomQueryByIDDate(QString roomID, QString checkInDate, QString checkOutDate);

    static bool exec_query(QString query);
public:
    static QList<room> selectAllRooms(QString query = "SELECT* FROM room");
    static QList<room> selectRoomsByQuery(QString roomID, QString roomType, QString customerID, QString priceFrom,
                                            QString priceTo, QString status, QString inDate, QString outDate, QString authority, QString managerID);
    static QList<room> selectRoomsByManagerID(QString ManagerID);
    static bool checkInUpdate(QString roomID, QString checkInDate, QString checkOutDate);
    static bool checkOutUpdate(QString roomID);
    static bool Update(QString roomID, QString checkInDate, QString checkOutDate);
};

#endif // ROOMSERVICE_H
