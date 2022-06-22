#include "customer.h"

customer::customer()
{

}

customer::customer(QString customerID, const QString &customerName, const QString &phoneNumber,
         const QString &customerAddress, const QString &accountNumber, int roomID):
    customer_id(customerID), customer_name(customerName), phone_number(phoneNumber),
    customer_address(customerAddress), account_number(accountNumber), room_id(roomID)
{

}

QString customer::getCustomer_id() const
{
    return customer_id;
}

void customer::setCustomer_id(QString customerID)
{
    customer_id = customerID;
}

QString customer::getCustomer_name() const
{
    return customer_name;
}

void customer::setCustomer_name(const QString &customerName)
{
    customer_name = customerName;
}

QString customer::getPhone_number() const
{
    return phone_number;
}

void customer::setPhone_number(const QString &phoneNumber)
{
    phone_number = phoneNumber;
}

QString customer::getCustomer_address() const
{
    return customer_address;
}

void customer::setCustomer_address(const QString &customerAddress)
{
    customer_address = customerAddress;
}

QString customer::getAccount_number() const
{
    return account_number;
}

void customer::setAccount_number(const QString &accountNumber)
{
    account_number = accountNumber;
}

int customer::getRoom_id() const
{
    return room_id;
}

void customer::setRoom_id(int roomID)
{
    room_id = roomID;
}
