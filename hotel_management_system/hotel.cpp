#include "hotel.h"

hotel::hotel()
{

}

hotel::hotel(int id, QString address, int level, int zip, QString hotelName): hotel_id(id), hotel_address(address),
hotel_level(level), zip_code(zip), hotel_name(hotelName)
{

}

int hotel::getHotel_Id()
{
    return this->hotel_id;
}

void hotel::setHotel_Id(int id)
{
    this->hotel_id = id;
}

QString hotel::getHotel_Address()
{
    return this->hotel_address;
}

void hotel::setHotel_Address(QString address)
{
    this->hotel_address = address;
}

int hotel::getHotel_Level()
{
    return this->hotel_level;
}

void hotel::setHotel_Level(int level)
{
    this->hotel_level = level;
}

int hotel::getZip_Code()
{
    return this->zip_code;
}

void hotel::setZip_Code(int zip)
{
    this->zip_code = zip;
}

QString hotel::getHotel_Name()
{
    return this->hotel_name;
}

void hotel::setHotel_Name(QString hotelName)
{
    this->hotel_name = hotelName;
}

