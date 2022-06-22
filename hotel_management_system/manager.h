#ifndef MANAGER_H
#define MANAGER_H

#include <QString>

class manager
{
private:
    int manager_id;
    int hotel_id;
    QString manager_password;
    QString manager_name;
    QString phone_number;
    QString manager_address;
    QString manager_authority;
public:
    manager();
    manager(int managerID, int hotelID, const QString& managerPassword, const QString& managerName,
            const QString& phoneNumber, const QString& managerAddress, const QString& managerAuthority);
    int getManager_id() const;
    void setManager_id(int managerID);
    int getHotel_id() const;
    void setHotel_id(int hotelID);
    QString getManager_password() const;
    void setManager_password(const QString &managerPassword);
    QString getManager_name() const;
    void setManager_name(const QString &managerName);
    QString getPhone_number() const;
    void setPhone_number(const QString &phoneNumber);
    QString getManager_address() const;
    void setManager_address(const QString &managerAddress);
    QString getManager_authority() const;
    void setManager_authority(const QString &managerAuthority);
};

#endif // MANAGER_H
