#include "customerservice.h"
#include <QDebug>

customerService::customerService()
{

}
//Get Insert Query
QString customerService::getInsertQuery(QString customerID, QString customerName, QString phoneNumber, QString customerAddress, QString accountNumber, QString roomID)
{
    QString query = "INSERT INTO customer\n";
    query += "VALUES('" +customerID+"', '" + customerName+"', '" + phoneNumber
            +"', '"+customerAddress+"', '"+accountNumber+"', "+roomID+")";

    return query;
}
//Get delete query by roomID
QString customerService::getDeleteCustQuery(QString roomID)
{
    QString query = "DELETE FROM customer\n";
    query += "WHERE room_id = '" + roomID + "'";
    return query;
}
//get Select Query by roomID
QString customerService::getSelectCustQuery(QString roomID)
{
    QString query = "SELECT* FROM customer\n";
    query += "WHERE room_id = '" + roomID + "'";
    return query;
}
//Get Update customer query
QString customerService::getUpdateCustQuery(QString customerID, QString customerName, QString phoneNumber, QString customerAddress, QString accountNumber, QString roomID)
{
    QString query = "UPDATE customer\n";
    query += "SET customer_name = '" + customerName+"', phone_number = '" + phoneNumber
            +"', customer_address = '"+customerAddress+"', account_number = '"+accountNumber+"', room_id = "+roomID + "\n";
    query += "WHERE customer_id = '"+customerID+"'";

    return query;
}

bool customerService::exec_query(QString query)
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

bool customerService::checkInInsert(QString customerID, QString customerName, QString phoneNumber, QString customerAddress, QString accountNumber, QString roomID)
{
    QString query = getInsertQuery(customerID, customerName, phoneNumber, customerAddress, accountNumber, roomID);

    return exec_query(query);
}

bool customerService::checkOutDelete(QString roomID)
{
    QString query = getDeleteCustQuery(roomID);

    return exec_query(query);
}

bool customerService::updateCust(QString customerID, QString customerName, QString phoneNumber, QString customerAddress, QString accountNumber, QString roomID)
{
    QString query = getUpdateCustQuery(customerID, customerName, phoneNumber, customerAddress, accountNumber, roomID);

    return exec_query(query);
}

customer customerService::parseQStr(QList<QString> strList)
{
    QString customerID = "";
    QString customerName = "";
    QString phoneNumber = "";
    QString customerAddress = "";
    QString accountNumber = "";
    int roomID = 0;

    for (int i = 0; i < strList.size(); i++)
    {
        bool ok;
        switch (i) {
        case 0:
            customerID = strList[i];
            break;
        case 1:
            customerName = strList[i];
            break;
        case 2:
            phoneNumber = strList[i];
            break;
        case 3:
            customerAddress = strList[i];
            break;
        case 4:
            accountNumber = strList[i];
            break;
        case 5:
            roomID = strList[i].toInt(&ok, 10);
            break;
        default:
            qDebug() << "Something went wrong...";
            break;
        }
    }

    return customer(customerID,customerName,phoneNumber,customerAddress,accountNumber,roomID);
}

QList<customer> customerService::selectAllCustomers(QString query)
{
    QList<customer> list;

    QSqlDatabase db;
    bool ok = connectToDB("QMYSQL", "127.0.0.1", "db2", "root", "root", 3306, db);

    if (ok){
        QList<QList<QString>> results = selectData(query);

        for (int i = 0; i < results.size(); i++)
        {
            customer cust = parseQStr(results[i]);
            list.push_back(cust);
        }

        closeDB(db);
    }
    else
    {
        qDebug() << "connect mysql unsuccessfully...";
    }

    return list;
}

QList<customer> customerService::selectCustomersByQuery(QString roomID)
{
    QString query = getSelectCustQuery(roomID);

    return selectAllCustomers(query);
}
