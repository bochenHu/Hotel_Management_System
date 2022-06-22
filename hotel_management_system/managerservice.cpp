#include "managerservice.h"
#include <qDebug>

managerService::managerService()
{

}
//Select by id
QList<manager> managerService::selectManagerByID(QString managerID)
{
    return selectAllManagers("SELECT * FROM manager WHERE manager_id = '" + managerID + "'");
}

manager managerService::parseQStr(QList<QString> strList)
{
    int managerID = 0;
    int hotelID = 0;
    QString managerPassword = "";
    QString managerName = "";
    QString phoneNumber = "";
    QString managerAddress = "";
    QString managerAuthority = "";

    for (int i = 0; i < strList.size(); i++)
    {
        bool ok;
        switch (i) {
        case 0:
            managerID = strList[i].toInt(&ok, 10);
            break;
        case 1:
            hotelID = strList[i].toInt(&ok, 10);
            break;
        case 2:
            managerPassword = strList[i];
            break;
        case 3:
            managerName = strList[i];
            break;
        case 4:
            phoneNumber = strList[i];
            break;
        case 5:
            managerAddress = strList[i];
            break;
        case 6:
            managerAuthority = strList[i];
            break;
        default:
            qDebug() << "Something went wrong...";
            break;
        }
    }

    return manager(managerID, hotelID, managerPassword, managerName, phoneNumber, managerAddress, managerAuthority);
}
//Get insert query
QString managerService::getInsertQuery(QString managerID, QString hotelID, QString managerPwd, QString managerName, QString phoneNum, QString managerAddress)
{
    QString query = "INSERT INTO manager\n";
    query = query + "VALUES( " + managerID + ", " + hotelID + ", '" + managerPwd + "', '" + managerName
            + "', '" + phoneNum + "', '" +managerAddress+ "', 'normal')";

    return query;
}
//Get Max ManagerID by hotelID
QString managerService::getSelectMaxManagerIDQuery(QString hotelID)
{
    QString query = "SELECT MAX(manager_id) FROM manager\n";
    query = query + "WHERE hotel_id = " + hotelID;

    return query;
}

QList<manager> managerService::selectAllManagers(QString query)
{
    QList<manager> list;

    QSqlDatabase db;
    bool ok = connectToDB("QMYSQL", "127.0.0.1", "db2", "root", "root", 3306, db);

    if (ok){
        QList<QList<QString>> results = selectData(query);

        for (int i = 0; i < results.size(); i++)
        {
            manager m = parseQStr(results[i]);
            list.push_back(m);
        }

        closeDB(db);
    }
    else
    {
        qDebug() << "connect mysql unsuccessfully...";
    }

    return list;
}

bool managerService::exec_query(QString query)
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

bool managerService::InsertManager(QString managerID, QString hotelID, QString managerPwd, QString managerName, QString phoneNum, QString managerAddress)
{
    QString query = getInsertQuery(managerID, hotelID, managerPwd, managerName, phoneNum, managerAddress);

    return exec_query(query);
}

QString managerService::selectMaxManagerIdByHotelId(QString hotelID)
{
    QString ret = "";
    QSqlDatabase db;
    bool ok = connectToDB("QMYSQL", "127.0.0.1", "db2", "root", "root", 3306, db);

    QString sqlQuery = getSelectMaxManagerIDQuery(hotelID);

    if (ok){
        QSqlQuery query(sqlQuery);

        int count = query.record().count();

        if (count == 1)
        {
            while (query.next()) {
                ret = query.value(0).toString();
            }
        }

        closeDB(db);
    }
    else
    {
        qDebug() << "connect mysql unsuccessfully...";
    }

    return ret;
}

bool managerService::DeleteAll(QString query)
{
    return exec_query(query);
}

bool managerService::DeleteByManagerID(QString ManagerID)
{
    QString query = "DELETE FROM manager\n";
    query = query + "WHERE manager_id = '" +ManagerID+"'";

    return exec_query(query);
}

bool managerService::UpdateByManagerID(QString ManagerID, QString hotelID, QString managerPwd, QString managerName, QString phoneNum, QString managerAddress)
{
    QString query = "UPDATE manager\n";
    query = query + "SET hotel_id = "+hotelID+", manager_password = '"+managerPwd+"', manager_name = '"
            +managerName+"', phone_number = '"+phoneNum+"', manager_address = '"+managerAddress+"'\n";
    query = query + "WHERE manager_id = '"+ManagerID+"'";

    return  exec_query(query);
}

