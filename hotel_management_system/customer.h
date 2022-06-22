#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>

class customer
{
private:
    QString customer_id;
    QString customer_name;
    QString phone_number;
    QString customer_address;
    QString account_number;
    int room_id;
public:
    customer();
    customer(QString customerID, const QString &customerName, const QString &phoneNumber,
             const QString &customerAddress, const QString &accountNumber, int roomID);
    QString getCustomer_id() const;
    void setCustomer_id(QString customerID);
    QString getCustomer_name() const;
    void setCustomer_name(const QString &customerName);
    QString getPhone_number() const;
    void setPhone_number(const QString &phoneNumber);
    QString getCustomer_address() const;
    void setCustomer_address(const QString &customerAddress);
    QString getAccount_number() const;
    void setAccount_number(const QString &accountNumber);
    int getRoom_id() const;
    void setRoom_id(int roomID);
};

#endif // CUSTOMER_H
