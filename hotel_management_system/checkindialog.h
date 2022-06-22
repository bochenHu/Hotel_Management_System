#ifndef CHECKINDIALOG_H
#define CHECKINDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QDateTime>

class checkInDialog : public QDialog
{
    Q_OBJECT
private:
    QGridLayout vMainLayout;
    QGroupBox roomInfoBox;
    QGroupBox custInfoBox;
    QGroupBox operationBox;

    QLabel room_id_Label;
    QLineEdit room_id_Edit;
    QLabel room_type_Label;
    QLineEdit room_type_Edit;
    QLabel room_price_Label;
    QLineEdit room_price_Edit;
    QLabel room_status_Label;
    QLineEdit room_status_Edit;
    QLabel inDateLabel;
    QDateTimeEdit inDateEdit;
    QLabel outDateLabel;
    QDateTimeEdit outDateEdit;

    QLabel customer_id_Label;
    QLineEdit customer_id_Edit;
    QLabel customer_name_Label;
    QLineEdit customer_name_Edit;
    QLabel phone_number_Label;
    QLineEdit phone_number_Edit;
    QLabel customer_address_Label;
    QLineEdit customer_address_Edit;
    QLabel account_number_Label;
    QLineEdit account_number_Edit;

    QPushButton submitBtn;
    QPushButton cancelBtn;
private:
    void basic_setter();
    void init_roomInfoBx();
    void init_custInfoBx();
    void init_operationBx();

    void connectSlots();
protected slots:
    void onSubmitBtnClicked();
    void onCancelBtnClicked();

public:
    checkInDialog(QWidget *parent = 0);

    void setRoomID(QString roomID);
    void setRoomType(QString roomType);
    void setRoomPrice(QString roomPrice);
    void setRoomStatus(QString roomStatus);
};

#endif // CHECKINDIALOG_H
