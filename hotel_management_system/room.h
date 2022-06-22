#ifndef ROOM_H
#define ROOM_H

#include <QString>

class room
{
private:
    int room_id;
    QString room_type;
    int hotel_id;
    int room_price;
    QString room_status;
    QString check_in_date;
    QString check_out_date;
public:
    room();
    room(int roomID, const QString &roomType, int hotelID, int roomPrice, const QString &roomStatus,
         const QString &checkInDate, const QString &checkOutDate);
    int getRoom_id() const;
    void setRoom_id(int roomID);
    QString getRoom_type() const;
    void setRoom_type(const QString &roomType);
    int getHotel_id() const;
    void setHotel_id(int hotelID);
    int getRoom_price() const;
    void setRoom_price(int roomPrice);
    QString getRoom_status() const;
    void setRoom_status(const QString &roomStatus);
    QString getCheck_in_date() const;
    void setCheck_in_date(const QString &checkInDate);
    QString getCheck_out_date() const;
    void setCheck_out_date(const QString &checkOutDate);
};

#endif // ROOM_H
