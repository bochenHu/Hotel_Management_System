#ifndef ADDMANAGEWIDGET_H
#define ADDMANAGEWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

#include "managerservice.h"
#include "manager.h"

class addManageWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout vMainLayout;
    QGroupBox employeeInfoBox;

    QLabel manager_id_Label;
    QComboBox manager_id_ComboBox;
    QLabel manager_authority_Label;
    QLineEdit manager_authority_Edit;


    QLabel hotel_id_Label;
    QComboBox hotel_id_ComboBox;
    QLabel manager_password_Label;
    QLineEdit manager_password_Edit;
    QLabel manager_name_Label;
    QLineEdit manager_name_Edit;
    QLabel phone_number_Label;
    QLineEdit phone_number_Edit;
    QLabel manager_address_Label;
    QLineEdit manager_address_Edit;

    QPushButton addBtn;

    QList<manager> managers;
    QList<QString> managerIDs;

private:
    void basic_setter();
    void init_EmployeeInfoBx();
    void init_operationBx();
    void initManagers();
    void initManagersIDs();
    void initText();

    void connectSlots();


protected slots:
    void onAddBtnClicked();
    void onHotelIDComboxChanged();

public:
    addManageWidget(QWidget *parent = nullptr);
};

#endif // ADDMANAGEWIDGET_H
