#include "checkindialog.h"
#include <QGridLayout>
#include <QRegExpValidator>
#include <QRegExp>
#include <QChar>
#include <QMessageBox>
#include <QDebug>

#include "roomservice.h"
#include "customerservice.h"

checkInDialog::checkInDialog(QWidget *parent):
    QDialog(parent)
{
    basic_setter();
    setModal(true);
}

void checkInDialog::basic_setter()
{
    init_roomInfoBx();
    init_custInfoBx();
    init_operationBx();
    connectSlots();

    vMainLayout.setSpacing(10);
    vMainLayout.addWidget(&roomInfoBox, 0, 0 , 2, 2);
    vMainLayout.addWidget(&custInfoBox, 2, 0, 2, 2);
    vMainLayout.addWidget(&operationBox, 4, 1, 1, 1);

    resize(650,400);
    setMinimumSize(650,400);
    setLayout(&vMainLayout);
    setWindowTitle("Check in");
}

void checkInDialog::init_roomInfoBx()
{
    QGridLayout* layout = new QGridLayout();

    layout->setSpacing(10);
    layout->addWidget(&room_id_Label,0,0,1,1);
    layout->addWidget(&room_id_Edit,0,1,1,3);
    layout->addWidget(&room_type_Label,0,4,1,1);
    layout->addWidget(&room_type_Edit,0,5,1,3);
    room_id_Label.setText(" Room ID:");
    room_type_Label.setText(" Room Type:");
    room_id_Edit.setFixedHeight(23);
    room_type_Edit.setFixedHeight(23);
    room_id_Edit.setEnabled(false);
    room_type_Edit.setEnabled(false);


    layout->addWidget(&room_price_Label,1,0,1,1);
    layout->addWidget(&room_price_Edit,1,1,1,3);
    layout->addWidget(&room_status_Label,1,4,1,1);
    layout->addWidget(&room_status_Edit,1,5,1,3);
    room_price_Label.setText(" Room Price:");
    room_status_Label.setText(" Room Status:");
    room_price_Edit.setFixedHeight(23);
    room_status_Edit.setFixedHeight(23);
    room_price_Edit.setEnabled(false);
    room_status_Edit.setEnabled(false);


    layout->addWidget(&inDateLabel,2,0,1,1);
    layout->addWidget(&inDateEdit,2,1,1,3);
    layout->addWidget(&outDateLabel,2,4,1,1);
    layout->addWidget(&outDateEdit,2,5,1,3);
    inDateLabel.setText(" Check In Date:");
    outDateLabel.setText(" Check out Date:");
    inDateEdit.setFixedHeight(23);
    outDateEdit.setFixedHeight(23);

    inDateEdit.setCalendarPopup(true);
    inDateEdit.setDateTime(QDateTime(QDate::currentDate(),QTime::currentTime()));
    outDateEdit.setCalendarPopup(true);
    outDateEdit.setDateTime(QDateTime(QDate::currentDate(),QTime::currentTime()));

    roomInfoBox.setMaximumHeight(160);
    roomInfoBox.setLayout(layout);
    roomInfoBox.setTitle("Room Info");
}

void checkInDialog::init_custInfoBx()
{
    QGridLayout* layout = new QGridLayout();

    layout->setSpacing(10);
    layout->addWidget(&customer_id_Label,0,0,1,1);
    layout->addWidget(&customer_id_Edit,0,1,1,3);
    layout->addWidget(&customer_name_Label,0,4,1,1);
    layout->addWidget(&customer_name_Edit,0,5,1,3);
    customer_id_Label.setText(" Customer ID:");
    customer_name_Label.setText(" Customer Name:");
    customer_id_Edit.setFixedHeight(23);
    customer_name_Edit.setFixedHeight(23);
    QRegExpValidator* validator = new QRegExpValidator(QRegExp("^[0-9]+$"));
    customer_id_Edit.setValidator(validator);


    layout->addWidget(&phone_number_Label,1,0,1,1);
    layout->addWidget(&phone_number_Edit,1,1,1,3);
    layout->addWidget(&customer_address_Label,1,4,1,1);
    layout->addWidget(&customer_address_Edit,1,5,1,3);
    phone_number_Label.setText(" Phone Number:");
    customer_address_Label.setText(" Customer Address:");
    phone_number_Edit.setFixedHeight(23);
    customer_address_Edit.setFixedHeight(23);
    QRegExpValidator* validator_phoneNum = new QRegExpValidator(QRegExp("^[0-9]+$"));
    phone_number_Edit.setValidator(validator_phoneNum);


    layout->addWidget(&account_number_Label,2,0,1,1);
    layout->addWidget(&account_number_Edit,2,1,1,3);
    account_number_Label.setText(" Account Number:");
    account_number_Edit.setFixedHeight(23);
    QRegExpValidator* validator_accountNum = new QRegExpValidator(QRegExp("^[0-9]+$"));
    account_number_Edit.setValidator(validator_accountNum);

    custInfoBox.setMaximumHeight(160);
    custInfoBox.setLayout(layout);
    custInfoBox.setTitle("Customer Info");
}

void checkInDialog::init_operationBx()
{
    QGridLayout* layout = new QGridLayout();

    layout->setSpacing(10);
    layout->addWidget(&submitBtn,1, 3, 1, 1);
    layout->addWidget(&cancelBtn,1, 4, 1, 1);
    submitBtn.setText("Submit");
    cancelBtn.setText("Cancel");
    submitBtn.setFixedHeight(30);
    cancelBtn.setFixedHeight(30);

    operationBox.setMaximumHeight(100);
    operationBox.setLayout(layout);
    operationBox.setStyleSheet("QGroupBox{border:none}");
}

void checkInDialog::connectSlots()
{
    connect(&submitBtn, SIGNAL(clicked(bool)), this, SLOT(onSubmitBtnClicked()));
    connect(&cancelBtn, SIGNAL(clicked(bool)), this, SLOT(onCancelBtnClicked()));
}

void checkInDialog::onSubmitBtnClicked()
{
    //get text from room info Box
    QString roomID = room_id_Edit.text();
    QString checkInDate = inDateEdit.dateTime().toString(Qt::ISODate).replace(QChar('T'), QChar(' '));
    QString checkOutDate = outDateEdit.dateTime().toString(Qt::ISODate).replace(QChar('T'), QChar(' '));

    //get text from customer info Box
    QString customerID = customer_id_Edit.text();
    QString customerName = customer_name_Edit.text();
    QString phoneNumber = phone_number_Edit.text();
    QString customerAddress = customer_address_Edit.text();
    QString accountNumber = account_number_Edit.text();

    if(checkInDate >= checkOutDate)
    {
        QMessageBox::critical(this, "Error", "Check-out date should be later than the check-in date.");
        return;
    }

    //get avoid of the situation that input edit is null
    if (customerID == "" || customerName == "" || phoneNumber == "" || customerAddress == "" || accountNumber == "")
    {
        QMessageBox::critical(this, "Error", "All customer information should be input.");
        return;
    }

    bool updateResult = roomService::checkInUpdate(roomID, checkInDate, checkOutDate);
    if (!updateResult)
    {
        QMessageBox::critical(this, "Error", "Update room table unsuccessfully.");
        return;
    }

    bool insertResult = customerService::checkInInsert(customerID, customerName, phoneNumber, customerAddress, accountNumber, roomID);
    if (!insertResult)
    {
        QMessageBox::critical(this, "Error", "Insert customer table unsuccessfully.");
        return;
    }

    QMessageBox::information(this, "Check In", "Check in successfully.");

    //clear controls
    customer_id_Edit.clear();
    customer_name_Edit.clear();
    phone_number_Edit.clear();
    customer_address_Edit.clear();
    account_number_Edit.clear();
    inDateEdit.setDateTime(QDateTime(QDate::currentDate(),QTime::currentTime()));
    outDateEdit.setDateTime(QDateTime(QDate::currentDate(),QTime::currentTime()));

    //send signal to update Main window
    accept();
}

void checkInDialog::onCancelBtnClicked()
{
    close();
}

void checkInDialog::setRoomID(QString roomID)
{
    room_id_Edit.setText(roomID);
}

void checkInDialog::setRoomType(QString roomType)
{
    room_type_Edit.setText(roomType);
}

void checkInDialog::setRoomPrice(QString roomPrice)
{
    room_price_Edit.setText(roomPrice);
}

void checkInDialog::setRoomStatus(QString roomStatus)
{
    room_status_Edit.setText(roomStatus);
}
