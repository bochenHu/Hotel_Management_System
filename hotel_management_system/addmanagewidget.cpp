#include "addmanagewidget.h"

#include <QGridLayout>
#include <QRegExpValidator>
#include <QRegExp>
#include <QChar>
#include <QMessageBox>
#include <QStringList>
#include <QDebug>

addManageWidget::addManageWidget(QWidget *parent) : QWidget(parent)
{
    basic_setter();
}

void addManageWidget::basic_setter()
{
    init_EmployeeInfoBx();
    initManagers();
    initManagersIDs();
    initText();
    connectSlots();

    vMainLayout.setSpacing(10);
    vMainLayout.addWidget(&employeeInfoBox, 0, 0, 2, 2);

    setFixedSize(640,250);
    setLayout(&vMainLayout);
    setWindowTitle("Update");
}


void addManageWidget::init_EmployeeInfoBx()
{
    QGridLayout* layout = new QGridLayout();

    layout->setSpacing(10);
    layout->addWidget(&manager_id_Label,0,0,1,1);
    layout->addWidget(&manager_id_ComboBox,0,1,1,3);
    layout->addWidget(&manager_authority_Label,0,4,1,1);
    layout->addWidget(&manager_authority_Edit,0,5,1,3);
    manager_id_Label.setText("Manager ID:");
    manager_authority_Label.setText("Authority:");
    manager_id_ComboBox.setFixedHeight(23);
    manager_authority_Edit.setFixedHeight(23);
    manager_id_ComboBox.setEnabled(false);
    manager_authority_Edit.setEnabled(false);
    manager_authority_Edit.setText("normal");


    layout->addWidget(&manager_name_Label,1,0,1,1);
    layout->addWidget(&manager_name_Edit,1,1,1,3);
    layout->addWidget(&hotel_id_Label,1,4,1,1);
    layout->addWidget(&hotel_id_ComboBox,1,5,1,3);
    hotel_id_Label.setText("Hotel ID:");
    manager_password_Label.setText("Password:");
    hotel_id_ComboBox.setFixedHeight(23);
    manager_password_Edit.setFixedHeight(23);


    layout->addWidget(&manager_password_Label,2,0,1,1);
    layout->addWidget(&manager_password_Edit,2,1,1,3);
    layout->addWidget(&phone_number_Label,2,4,1,1);
    layout->addWidget(&phone_number_Edit,2,5,1,3);
    manager_name_Label.setText("Name:");
    phone_number_Label.setText("Phone Number:");
    manager_name_Edit.setFixedHeight(23);
    phone_number_Edit.setFixedHeight(23);
    QRegExpValidator * validator_phoneNum = new QRegExpValidator(QRegExp("^[0-9]+$"));
    phone_number_Edit.setValidator(validator_phoneNum);

    layout->addWidget(&manager_address_Label,3,0,1,1);
    layout->addWidget(&manager_address_Edit,3,1,1,3);
    manager_address_Label.setText("Address:");
    manager_address_Edit.setFixedHeight(23);

    layout->addWidget(&addBtn,4, 7);
    addBtn.setText("Add");
    addBtn.setFixedHeight(30);

    employeeInfoBox.setMaximumHeight(200);
    employeeInfoBox.setLayout(layout);
    employeeInfoBox.setTitle("New Employee Info");
}

void addManageWidget::initManagers()
{
    QList<manager> list = managerService::selectAllManagers();

    if (list.size() == 0){
        qDebug() << "initialize managers unsuccessfully...";
        return;
    }
    managers = list;
}

void addManageWidget::initManagersIDs()
{
    if (managers.size() == 0)
    {
        qDebug() << "managers is null...";
        return;
    }

    for (auto& manager: managers)
    {
        QString managerID = managerService::selectMaxManagerIdByHotelId(QString::number(manager.getHotel_id()));
        managerID = QString::number(managerID.toInt() + 1);
        managerIDs.push_back(managerID);
    }
}

void addManageWidget::initText()
{
    if (managerIDs.size() == 0)
    {
        qDebug() << "managerIDs is null...";
        return;
    }
    QStringList managerIDsList;
    for (auto& IDs: managerIDs)
    {
        if (!managerIDsList.contains(IDs))
        {
            managerIDsList.push_back(IDs);
        }
    }
    manager_id_ComboBox.addItems(managerIDsList);


    if (managers.size() == 0)
    {
        qDebug() << "managers is null...";
        return;
    }
    QStringList hotelIDsList;

    for (auto& manager: managers)
    {
        if (!hotelIDsList.contains(QString::number(manager.getHotel_id())))
        {
            hotelIDsList.push_back(QString::number(manager.getHotel_id()));
        }
    }
    hotel_id_ComboBox.addItems(hotelIDsList);
}

void addManageWidget::connectSlots()
{
    connect(&addBtn, SIGNAL(clicked(bool)), this, SLOT(onAddBtnClicked()));
    connect(&hotel_id_ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onHotelIDComboxChanged()));
}

void addManageWidget::onAddBtnClicked()
{
    QString managerID = manager_id_ComboBox.currentText();
    QString hotelID = hotel_id_ComboBox.currentText();
    QString managerPwd = manager_password_Edit.text();
    QString managerName = manager_name_Edit.text();
    QString phoneNum = phone_number_Edit.text();
    QString managerAddress = manager_address_Edit.text();

    if (managerPwd == "" || managerName == "" || phoneNum == "" || managerAddress == "")
    {
        QMessageBox::critical(this, "Error", "All manager information should be provided.");
        return;
    }

    bool isSuccess = managerService::InsertManager(managerID, hotelID, managerPwd, managerName, phoneNum, managerAddress);

    if (isSuccess){
        QMessageBox::information(this, "Add", "Add new manager successfully.");
        manager_name_Edit.clear();
        manager_address_Edit.clear();
        manager_password_Edit.clear();
        phone_number_Edit.clear();
    }
    else QMessageBox::critical(this, "Error", "Add new manager unsuccessfully.");
}

void addManageWidget::onHotelIDComboxChanged()
{
    int currIndex = hotel_id_ComboBox.currentIndex();

    manager_id_ComboBox.setCurrentIndex(currIndex);
}

