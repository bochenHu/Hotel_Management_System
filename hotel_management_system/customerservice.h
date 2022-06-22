#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QList>

#include "customer.h"
#include "sqlservice.h"

class customerService : public sqlService
{
private:
    customerService();
    static customer parseQStr(QList<QString> strList);
    static QString getInsertQuery(QString customerID, QString customerName, QString phoneNumber, QString customerAddress, QString accountNumber, QString roomID);
    static QString getDeleteCustQuery(QString roomID);
    static QString getSelectCustQuery(QString roomID);
    static QString getUpdateCustQuery(QString customerID, QString customerName, QString phoneNumber, QString customerAddress, QString accountNumber, QString roomID);

    static bool exec_query(QString query);
public:
    static bool checkInInsert(QString customerID, QString customerName, QString phoneNumber, QString customerAddress, QString accountNumber, QString roomID);
    static bool checkOutDelete(QString roomID);
    static bool updateCust(QString customerID, QString customerName, QString phoneNumber, QString customerAddress, QString accountNumber, QString roomID);
    static QList<customer> selectAllCustomers(QString query="SELECT* FROM customer");
    static QList<customer> selectCustomersByQuery(QString roomID);
};

#endif // CUSTOMERSERVICE_H
