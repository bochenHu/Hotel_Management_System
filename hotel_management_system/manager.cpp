#include "manager.h"

manager::manager()
{

}

manager::manager(int managerID, int hotelID, const QString& managerPassword, const QString& managerName,
                 const QString& phoneNumber, const QString& managerAddress, const QString& managerAuthority):
    manager_id(managerID), hotel_id(hotelID), manager_password(managerPassword), manager_name(managerName),
    phone_number(phoneNumber), manager_address(managerAddress), manager_authority(managerAuthority)
{

}

int manager::getManager_id() const
{
    return manager_id;
}

void manager::setManager_id(int managerID)
{
    manager_id = managerID;
}

int manager::getHotel_id() const
{
    return hotel_id;
}

void manager::setHotel_id(int hotelID)
{
    hotel_id = hotelID;
}

QString manager::getManager_password() const
{
    return manager_password;
}

void manager::setManager_password(const QString &managerPassword)
{
    manager_password = managerPassword;
}

QString manager::getManager_name() const
{
    return manager_name;
}

void manager::setManager_name(const QString &managerName)
{
    manager_name = managerName;
}

QString manager::getPhone_number() const
{
    return phone_number;
}

void manager::setPhone_number(const QString &phoneNumber)
{
    phone_number = phoneNumber;
}

QString manager::getManager_address() const
{
    return manager_address;
}

void manager::setManager_address(const QString &managerAddress)
{
    manager_address = managerAddress;
}

QString manager::getManager_authority() const
{
    return manager_authority;
}

void manager::setManager_authority(const QString &managerAuthority)
{
    manager_authority = managerAuthority;
}
