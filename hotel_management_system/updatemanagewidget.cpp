#include "updatemanagewidget.h"

#include <QGridLayout>
#include <QRegExp>
#include <QRegExpValidator>
#include <QChar>
#include <QMessageBox>
#include <QStringList>
#include <QDebug>


updateManageWidget::updateManageWidget(QWidget *parent) : QWidget(parent)
{
    basic_setter();
}

void updateManageWidget::basic_setter()
{
    init_EmployeeBx();
    init_EmployeeInfoBx();
    set_ControlsEnabled(false);
    init_managers();
    init_Text();
    connectSlots();

    vMainLayout.setSpacing(10);
    vMainLayout.addWidget(&employeeBox, 0, 0 , 1, 2);
    vMainLayout.addWidget(&employeeInfoBox, 1, 0, 2, 2);

    setFixedSize(640,400);
    setLayout(&vMainLayout);
    setWindowTitle("Update");
    setWindowFlags(Qt::WindowCloseButtonHint|Qt::MSWindowsFixedSizeDialogHint);
}

void updateManageWidget::init_EmployeeBx()
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
    manager_authority_Edit.setEnabled(false);

    employeeBox.setMaximumHeight(160);
    employeeBox.setLayout(layout);
    employeeBox.setTitle("Employees");
}

void updateManageWidget::init_EmployeeInfoBx()
{
    QGridLayout* layout = new QGridLayout();

    layout->setSpacing(10);
    layout->addWidget(&manager_name_Label,0,0,1,1);
    layout->addWidget(&manager_name_Edit,0,1,1,3);
    layout->addWidget(&hotel_id_Label,0,4,1,1);
    layout->addWidget(&hotel_id_ComboBox,0,5,1,3);
    hotel_id_Label.setText("Hotel ID:");
    manager_password_Label.setText("Password:");
    hotel_id_ComboBox.setFixedHeight(23);
    manager_password_Edit.setFixedHeight(23);


    layout->addWidget(&manager_password_Label,1,0,1,1);
    layout->addWidget(&manager_password_Edit,1,1,1,3);
    layout->addWidget(&phone_number_Label,1,4,1,1);
    layout->addWidget(&phone_number_Edit,1,5,1,3);
    manager_name_Label.setText("Name:");
    phone_number_Label.setText("Phone Number:");
    manager_name_Edit.setFixedHeight(23);
    phone_number_Edit.setFixedHeight(23);
    QRegExpValidator* validator_phoneNum = new QRegExpValidator(QRegExp("^[0-9]+$"));
    phone_number_Edit.setValidator(validator_phoneNum);


    layout->addWidget(&manager_address_Label,2,0,1,1);
    layout->addWidget(&manager_address_Edit,2,1,1,3);
    manager_address_Label.setText("Address:");
    manager_address_Edit.setFixedHeight(23);


    layout->addWidget(&deleteBtn, 3, 6);
    layout->addWidget(&editBtn, 3, 7);
    deleteBtn.setText("Delete");
    editBtn.setText("Edit");
    deleteBtn.setFixedHeight(30);
    editBtn.setFixedHeight(30);

    employeeInfoBox.setMaximumHeight(160);
    employeeInfoBox.setLayout(layout);
    employeeInfoBox.setTitle("Employee Info");
}

void updateManageWidget::set_ControlsEnabled(bool enabled)
{
    manager_name_Edit.setEnabled(enabled);
    hotel_id_ComboBox.setEnabled(enabled);
    manager_password_Edit.setEnabled(enabled);
    phone_number_Edit.setEnabled(enabled);
    manager_address_Edit.setEnabled(enabled);
}

void updateManageWidget::init_managers()
{
    QList<manager> list = managerService::selectAllManagers();

    if (list.size() == 0){
        qDebug() << "initialize managers unsuccessfully...";
        return;
    }
    managers = list;
}

void updateManageWidget::init_Text()
{
    QStringList managerIDs;
    QStringList hotelIDs;
    for (auto& manager: managers){
        managerIDs.push_back(QString::number(manager.getManager_id()));
        if (!hotelIDs.contains(QString::number(manager.getHotel_id())))
            hotelIDs.push_back(QString::number(manager.getHotel_id()));
    }
    manager_id_ComboBox.addItems(managerIDs);
    manager_authority_Edit.setText(managers[manager_id_ComboBox.currentIndex()].getManager_authority());
    hotel_id_ComboBox.addItems(hotelIDs);
    manager_password_Edit.setText(managers[manager_id_ComboBox.currentIndex()].getManager_password());
    manager_name_Edit.setText(managers[manager_id_ComboBox.currentIndex()].getManager_name());
    phone_number_Edit.setText(managers[manager_id_ComboBox.currentIndex()].getPhone_number());
    manager_address_Edit.setText(managers[manager_id_ComboBox.currentIndex()].getManager_address());
}

void updateManageWidget::connectSlots()
{
    connect(&deleteBtn, SIGNAL(clicked(bool)), this, SLOT(onDeleteBtnClicked()));
    connect(&editBtn, SIGNAL(clicked(bool)), this, SLOT(onEditBtnClicked()));
    connect(&manager_id_ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onUpdateText()));
}

void updateManageWidget::onDeleteBtnClicked()
{
    if (managers.size() > 0)
    {
        QString authority = manager_authority_Edit.text();
        if (authority == "super")
        {
            QMessageBox::critical(this, "Error", "You do not have a permission to delete a super manager.");
            return;
        }

        QMessageBox msgBx(this);
        msgBx.setIcon(QMessageBox::Icon::Information);
        msgBx.setWindowTitle("Hint");
        msgBx.setInformativeText("Are you sure to delete the manager?");
        msgBx.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBx.setDefaultButton(QMessageBox::Ok);
        msgBx.setFixedSize(219,172);
        int ret = msgBx.exec();
        if (ret != QMessageBox::Ok) return;

        bool isSuccess = managerService::DeleteByManagerID(manager_id_ComboBox.currentText());

        if (isSuccess)
        {
            int currIndex = manager_id_ComboBox.currentIndex();

            managers.removeAt(currIndex);
            manager_id_ComboBox.removeItem(currIndex);
            hotel_id_ComboBox.removeItem(currIndex);
            manager_id_ComboBox.setCurrentIndex(0);
            manager_authority_Edit.setText(managers[0].getManager_authority());
            hotel_id_ComboBox.setCurrentIndex(0);
            manager_password_Edit.setText(managers[0].getManager_password());
            manager_name_Edit.setText(managers[0].getManager_name());
            phone_number_Edit.setText(managers[0].getPhone_number());
            manager_address_Edit.setText(managers[0].getManager_address());

            QMessageBox::information(this, "Delete", "Delete the manager successfully.");
        }
        else
        {
            QMessageBox::critical(this, "Delete", "Delete the manager unsuccessfully.");
        }
    }
    else
    {
        manager_id_ComboBox.clear();
        manager_authority_Edit.clear();
        hotel_id_ComboBox.clear();
        manager_password_Edit.clear();
        manager_name_Edit.clear();
        phone_number_Edit.clear();
        manager_address_Edit.clear();
    }
}

void updateManageWidget::onEditBtnClicked()
{
    if (editBtn.text() == "Edit")
    {
        editBtn.setText("Save");
        set_ControlsEnabled(true);
    }
    else
    {
        QMessageBox msgBx;
        msgBx.setIcon(QMessageBox::Icon::Information);
        msgBx.setWindowTitle("Hint");
        msgBx.setInformativeText("Are you sure you want to update the manager?");
        msgBx.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBx.setDefaultButton(QMessageBox::Ok);
        msgBx.setFixedSize(348,152);
        int ret = msgBx.exec();
        if (ret != QMessageBox::Ok) return;

        QString managerID = manager_id_ComboBox.currentText();
        QString hotelID = hotel_id_ComboBox.currentText();
        QString managerAddress = manager_address_Edit.text();
        QString managerName = manager_name_Edit.text();
        QString managerPwd = manager_password_Edit.text();
        QString phoneNumber = phone_number_Edit.text();

        if (managerAddress == "" || managerName == ""
                || managerPwd == "" || phoneNumber == ""){
            QMessageBox::critical(this, "Error", "Updated information should all be provided.");
            return;
        }

        bool isSuccess = managerService::UpdateByManagerID(managerID, hotelID, managerPwd, managerName, phoneNumber, managerAddress);

        if (isSuccess)
        {
            editBtn.setText("Edit");
            set_ControlsEnabled(false);
            int currIndex = manager_id_ComboBox.currentIndex();
            managers[currIndex].setHotel_id(hotel_id_ComboBox.currentText().toInt());
            managers[currIndex].setManager_address(manager_address_Edit.text());
            managers[currIndex].setManager_authority(manager_authority_Edit.text());
            managers[currIndex].setManager_name(manager_name_Edit.text());
            managers[currIndex].setManager_password(manager_password_Edit.text());
            managers[currIndex].setPhone_number(phone_number_Edit.text());

            QMessageBox::information(this, "Update", "Update the manager successfully.");
        }
        else
        {
            QMessageBox::critical(this, "Update", "Update the manager unsuccessfully.");
        }
    }
}

void updateManageWidget::onUpdateText()
{
    int currentIndex = manager_id_ComboBox.currentIndex();

    manager_authority_Edit.setText(managers[currentIndex].getManager_authority());
    for (int i = 0; i < hotel_id_ComboBox.count(); i++)
    {
        if (QString::number(managers[currentIndex].getHotel_id()) == hotel_id_ComboBox.itemText(i))
            hotel_id_ComboBox.setCurrentIndex(i);
    }
    manager_password_Edit.setText(managers[currentIndex].getManager_password());
    manager_name_Edit.setText(managers[currentIndex].getManager_name());
    phone_number_Edit.setText(managers[currentIndex].getPhone_number());
    manager_address_Edit.setText(managers[currentIndex].getManager_address());
}
