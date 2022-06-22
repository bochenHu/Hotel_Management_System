#ifndef HOTEL_H
#define HOTEL_H
#include <QString>

class hotel
{
private:
    int hotel_id;
    QString hotel_address;
    int hotel_level;
    int zip_code;
    QString hotel_name;
public:
    hotel();
    hotel(int id, QString address, int level, int zip, QString hotelName);
    int getHotel_Id();
    void setHotel_Id(int id);
    QString getHotel_Address();
    void setHotel_Address(QString address);
    int getHotel_Level();
    void setHotel_Level(int level);
    int getZip_Code();
    void setZip_Code(int zip);
    QString getHotel_Name();
    void setHotel_Name(QString hotelName);
};

#endif // HOTEL_H
