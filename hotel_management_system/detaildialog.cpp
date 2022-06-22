#include "detaildialog.h"

#include <QGridLayout>
#include <QRegExpValidator>
#include <QRegExp>
#include <QChar>
#include <QMessageBox>
#include <QDebug>

#include "roomservice.h"
#include "customerservice.h"

detailDialog::detailDialog(QWidget *parent):
    QDialog(parent)
{
    basic_setter();
    setModal(true);
}

void detailDialog::basic_setter()
{
    init_roomInfoBx();
    init_custInfoBx();
    init_operationBx();
    control_SetEnabled(false);
    connectSlots();

    vMainLayout.setSpacing(10);
    vMainLayout.addWidget(&roomInfoBox, 0, 0 , 2, 2);
    vMainLayout.addWidget(&custInfoBox, 2, 0, 2, 2);
    vMainLayout.addWidget(&operationBox, 4, 1, 1, 1);

    setWindowTitle(QString("Check In"));
    resize(650,400);
    setMinimumSize(650,400);
    setLayout(&vMainLayout);
    setWindowTitle("Detail");
}

void detailDialog::init_roomInfoBx()
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

void detailDialog::init_custInfoBx()
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

void detailDialog::init_operationBx()
{
    QGridLayout* layout = new QGridLayout();

    layout->setSpacing(10);
    layout->addWidget(&updateBtn,1, 3, 1, 1);
    layout->addWidget(&cancelBtn,1, 4, 1, 1);
    updateBtn.setText("Update");
    cancelBtn.setText("Cancel");
    updateBtn.setFixedHeight(30);
    cancelBtn.setFixedHeight(30);

    operationBox.setMaximumHeight(100);
    operationBox.setLayout(layout);
    operationBox.setStyleSheet("QGroupBox{border:none}");
}

void detailDialog::control_SetEnabled(bool enabled)
{
    inDateEdit.setEnabled(enabled);
    outDateEdit.setEnabled(enabled);
    customer_id_Edit.setEnabled(enabled);
    customer_name_Edit.setEnabled(enabled);
    phone_number_Edit.setEnabled(enabled);
    customer_address_Edit.setEnabled(enabled);
    account_number_Edit.setEnabled(enabled);
}

void detailDialog::connectSlots()
{
    connect(&updateBtn, SIGNAL(clicked(bool)), this, SLOT(onUpdateBtnClicked()));
    connect(&cancelBtn, SIGNAL(clicked(bool)), this, SLOT(onCancelBtnClicked()));
}

void detailDialog::setRoomID(QString roomID)
{
    room_id_Edit.setText(roomID);
}

void detailDialog::setRoomType(QString roomType)
{
    room_type_Edit.setText(roomType);
}

void detailDialog::setRoomPrice(QString roomPrice)
{
    room_price_Edit.setText(roomPrice);
}

void detailDialog::setRoomStatus(QString roomStatus)
{
    room_status_Edit.setText(roomStatus);
}

void detailDialog::setInDate(QDateTime inDate)
{
    inDateEdit.setDateTime(inDate);
}

void detailDialog::setOutDate(QDateTime outDate)
{
    outDateEdit.setDateTime(outDate);
}

void detailDialog::setCustID(QString customerID)
{
    customer_id_Edit.setText(customerID);
}

void detailDialog::setCustName(QString customerName)
{
    customer_name_Edit.setText(customerName);
}

void detailDialog::setPhoneNumber(QString phoneNumber)
{
    phone_number_Edit.setText(phoneNumber);
}

void detailDialog::setCustomerAddress(QString CustAddress)
{
    customer_address_Edit.setText(CustAddress);
}

void detailDialog::setAccountNumber(QString accountNumber)
{
    account_number_Edit.setText(accountNumber);
}

void detailDialog::onUpdateBtnClicked()
{
    if (updateBtn.text() == "Update")
    {
        control_SetEnabled(true);
        updateBtn.setText("Submit");
    }
    else if (updateBtn.text() == "Submit")
    {
        QString roomID = room_id_Edit.text();
        QString roomStatus = room_status_Edit.text();
        QString inDate = inDateEdit.dateTime().toString(Qt::ISODate).replace(QChar('T'), QChar(' '));
        QString outDate = outDateEdit.dateTime().toString(Qt::ISODate).replace(QChar('T'), QChar(' '));
        if (inDate >= outDate)
        {
            QMessageBox::critical(this, "Error", "Check-in Date should be later than the check-out Date.");
            return;
        }

        QString customerID = customer_id_Edit.text();
        QString customerName = customer_name_Edit.text();
        QString phoneNumber = phone_number_Edit.text();
        QString customerAddress = customer_address_Edit.text();
        QString accountNumber = account_number_Edit.text();
        if (customerID == "" || customerName == "" || phoneNumber == "" || customerAddress == "" || accountNumber == "")
        {
            QMessageBox::critical(this, "Error", "All customer information cannot be null.");
            return;
        }

        bool isSuccess = roomService::Update(roomID, inDate, outDate);
        if (isSuccess)
        {
            bool isSuccess = customerService::updateCust(customerID, customerName, phoneNumber, customerAddress, accountNumber, roomID);
            if (isSuccess)
            {
                control_SetEnabled(false);
                updateBtn.setText("Update");
                QMessageBox::information(this, "Success", "Update data successfully.");

                accept();
            }
            else
            {
                QMessageBox::critical(this, "Error", "Update Customer unsuccessfully.");
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "Update Room unsuccessfully.");
        }

    }
}

void detailDialog::onCancelBtnClicked()
{
    updateBtn.setText("Update");
    control_SetEnabled(false);
    close();
}
