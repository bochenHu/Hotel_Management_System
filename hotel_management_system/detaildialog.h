#ifndef DETAILDIALOG_H
#define DETAILDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QDateTime>


class detailDialog : public QDialog
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

    QPushButton updateBtn;
    QPushButton cancelBtn;
private:
    void basic_setter();
    void init_roomInfoBx();
    void init_custInfoBx();
    void init_operationBx();
    void control_SetEnabled(bool enabled = true);

    void connectSlots();
protected slots:
    void onUpdateBtnClicked();
    void onCancelBtnClicked();

public:
    detailDialog(QWidget *parent = 0);

    void setRoomID(QString roomID);
    void setRoomType(QString roomType);
    void setRoomPrice(QString roomPrice);
    void setRoomStatus(QString roomStatus);
    void setInDate(QDateTime inDate);
    void setOutDate(QDateTime outDate);
    void setCustID(QString customerID);
    void setCustName(QString customerName);
    void setPhoneNumber(QString phoneNumber);
    void setCustomerAddress(QString CustAddress);
    void setAccountNumber(QString accountNumber);
};

#endif // DETAILDIALOG_H
