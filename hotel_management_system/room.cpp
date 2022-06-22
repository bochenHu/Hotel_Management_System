#include "room.h"

room::room()
{

}

room::room(int roomID, const QString &roomType, int hotelID, int roomPrice, const QString &roomStatus,
     const QString &checkInDate, const QString &checkOutDate):
    room_id(roomID), room_type(roomType), hotel_id(hotelID), room_price(roomPrice),
    room_status(roomStatus), check_in_date(checkInDate), check_out_date(checkOutDate)
{

}

int room::getRoom_id() const
{
    return room_id;
}

void room::setRoom_id(int roomID)
{
    room_id = roomID;
}

QString room::getRoom_type() const
{
    return room_type;
}

void room::setRoom_type(const QString &roomType)
{
    room_type = roomType;
}

int room::getHotel_id() const
{
    return hotel_id;
}

void room::setHotel_id(int hotelID)
{
    hotel_id = hotelID;
}

int room::getRoom_price() const
{
    return room_price;
}

void room::setRoom_price(int roomPrice)
{
    room_price = roomPrice;
}

QString room::getRoom_status() const
{
    return room_status;
}

void room::setRoom_status(const QString &roomStatus)
{
    room_status = roomStatus;
}

QString room::getCheck_in_date() const
{
    return check_in_date;
}

void room::setCheck_in_date(const QString &checkInDate)
{
    check_in_date = checkInDate;
}

QString room::getCheck_out_date() const
{
    return check_out_date;
}

void room::setCheck_out_date(const QString &checkOutDate)
{
    check_out_date = checkOutDate;
}
