#include "roomservice.h"
#include <qDebug>

roomService::roomService()
{

}

room roomService::parseQStr(QList<QString> strList)
{
    int room_id = 0;
    QString room_type = "";
    int hotel_id = 0;
    int room_price = 0;
    QString room_status = "";
    QString check_in_date = "";
    QString check_out_date = "";

    for (int i = 0; i < strList.size(); i++)
    {
        bool ok;
        switch (i) {
        case 0:
            room_id = strList[i].toInt(&ok, 10);
            break;
        case 1:
            room_type = strList[i];
            break;
        case 2:
            hotel_id = strList[i].toInt(&ok, 10);
            break;
        case 3:
            room_price = strList[i].toInt(&ok, 10);
            break;
        case 4:
            room_status = strList[i];
            break;
        case 5:
            check_in_date = strList[i];
            break;
        case 6:
            check_out_date = strList[i];
            break;
        default:
            qDebug() << "Something went wrong...";
            break;
        }
    }

    return room(room_id, room_type, hotel_id, room_price, room_status, check_in_date, check_out_date);
}

QString roomService::getQueryByManagerID(QString ManagerID)
{
    QString query = "SELECT * FROM room\n";
    query += "WHERE hotel_id = (\n";
    query += "SELECT hotel_id FROM manager\n";
    query = query + "WHERE manager_id = '" + ManagerID + "'";
    query += ");";
    return query;
}

//get UpdateQuery which is used for check in operation
QString roomService::getUpdateQuery(QString roomID, QString checkInDate, QString checkOutDate)
{
    QString query = "UPDATE room\n";
    query += "SET room_status = 'Checked', check_in_date = '" + checkInDate + "', check_out_date = '" +checkOutDate + "'\n";
    query += "WHERE room_id = '" + roomID+ "'";

    return query;
}

//Update Room query by roomID
QString roomService::getUpdateRoomQuery(QString roomID)
{
    QString query = "UPDATE room\n";
    query += "SET room_status = 'Empty', check_in_date = NULL, check_out_date = NULL\n";
    query = query + "WHERE room_id = '" + roomID +"'";

    return query;
}

//get UpdateQuery which is used for check in operation
QString roomService::getUpdateRoomQueryByIDDate(QString roomID, QString checkInDate, QString checkOutDate)
{
    QString query = "UPDATE room\n";
    query += "SET room_status = 'Checked', check_in_date = '" + checkInDate + "', check_out_date = '" +checkOutDate + "'\n";
    query += "WHERE room_id = '" + roomID+ "'";

    return query;
}

QList<room> roomService::selectAllRooms(QString query)
{
    QList<room> list;

    QSqlDatabase db;
    bool ok = connectToDB("QMYSQL", "127.0.0.1", "db2", "root", "root", 3306, db);

    if (ok){
        QList<QList<QString>> results = selectData(query);

        for (int i = 0; i < results.size(); i++)
        {
            room rm = parseQStr(results[i]);
            list.push_back(rm);
        }

        closeDB(db);
    }
    else
    {
        qDebug() << "connect mysql unsuccessfully...";
    }

    return list;
}

QList<room> roomService::selectRoomsByQuery(QString roomID, QString roomType, QString customerID, QString priceFrom,
                                            QString priceTo, QString status, QString inDate, QString outDate, QString authority, QString managerID)
{
    //get query language
    QString sqlQuery = "SELECT * FROM room\n";
    if ((roomID=="" && roomType=="" && customerID=="" && priceFrom=="" &&
          priceTo=="" && status=="" && inDate == outDate && authority == "super"))  return selectAllRooms(sqlQuery);
    else if ((roomID=="" && roomType=="" && customerID=="" && priceFrom=="" &&
              priceTo=="" && status=="" && inDate == outDate && authority != "super"))
    {
        sqlQuery += "WHERE hotel_id = (\n";
        sqlQuery += "SELECT hotel_id FROM manager\n";
        sqlQuery = sqlQuery + "WHERE manager_id = '" + managerID + "'";
        sqlQuery += ");";
        return selectAllRooms(sqlQuery);
    }

    sqlQuery += "WHERE ";
    if (roomID != "")
    {
        if (!(sqlQuery.endsWith("WHERE "))) sqlQuery += "AND ";
        sqlQuery = sqlQuery + "room_id = " + roomID + "\n";
    }
    if (roomType != "")
    {
        if (!(sqlQuery.endsWith("WHERE "))) sqlQuery += "AND ";
        sqlQuery = sqlQuery + "room_type = '" + roomType + "'\n";
    }
    if (priceFrom != "")
    {
        if (!(sqlQuery.endsWith("WHERE "))) sqlQuery += "AND ";
        sqlQuery = sqlQuery + "room_price >= " + priceFrom + "\n";
    }
    if (priceTo != "")
    {
        if (!(sqlQuery.endsWith("WHERE "))) sqlQuery += "AND ";
        sqlQuery = sqlQuery + "room_price <= " + priceTo + "\n";
    }
    if (status != "")
    {
        if (!(sqlQuery.endsWith("WHERE "))) sqlQuery += "AND ";
        sqlQuery = sqlQuery + "room_status = '" + status + "'\n";
    }
    if (inDate != outDate)
    {
        if (!(sqlQuery.endsWith("WHERE "))) sqlQuery += "AND ";
        sqlQuery = sqlQuery + "check_in_date >= '" + inDate + "'\n";
        sqlQuery = sqlQuery + "AND check_out_date <= '" + outDate + "'\n";
    }
    if (customerID != "")
    {
        if (!(sqlQuery.endsWith("WHERE "))) sqlQuery += "AND ";
        sqlQuery = sqlQuery + "room_id = \n(\nSELECT room_id \nFROM customer \nWHERE customer_id = " + customerID + ")\n";
    }

    if (authority != "super")
    {
        QString query = "SELECT * from (\n";
        sqlQuery = query + sqlQuery;
        sqlQuery += ") AS temp\n";
        sqlQuery += "WHERE hotel_id = (\n";
        sqlQuery += "SELECT hotel_id FROM manager\n";
        sqlQuery = sqlQuery + "WHERE manager_id = " + managerID +"\n";
        sqlQuery += ")";
    }
    qDebug() << sqlQuery.toStdString().c_str();

    return selectAllRooms(sqlQuery);
}

QList<room> roomService::selectRoomsByManagerID(QString ManagerID)
{
    QString queryByManagerID = getQueryByManagerID(ManagerID).toStdString().c_str();
    return selectAllRooms(queryByManagerID);
}

bool roomService::exec_query(QString query)
{
    bool ret = false;
    QSqlDatabase db;
    ret = connectToDB("QMYSQL", "127.0.0.1", "db2", "root", "root", 3306, db);

    if (ret){
        ret = operateData(query);

        closeDB(db);
    }

    return ret;
}

bool roomService::checkInUpdate(QString roomID, QString checkInDate, QString checkOutDate)
{
    QString query = getUpdateQuery(roomID, checkInDate, checkOutDate);

    return exec_query(query);
}

bool roomService::checkOutUpdate(QString roomID)
{
    QString query = getUpdateRoomQuery(roomID);

    return exec_query(query);
}

bool roomService::Update(QString roomID, QString checkInDate, QString checkOutDate)
{
    QString query = getUpdateRoomQueryByIDDate(roomID, checkInDate, checkOutDate);

    return exec_query(query);
}
