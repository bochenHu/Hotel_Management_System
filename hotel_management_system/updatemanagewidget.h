#ifndef UPDATEMANAGEWIDGET_H
#define UPDATEMANAGEWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QList>

#include "managerservice.h"

class updateManageWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout vMainLayout;
    QGroupBox employeeBox;
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
    QPushButton deleteBtn;
    QPushButton editBtn;

    QList<manager> managers;

private:
    void basic_setter();
    void init_EmployeeBx();
    void init_EmployeeInfoBx();
    void init_operationBx();
    void set_ControlsEnabled(bool enabled);
    void init_managers();
    void init_Text();

    void connectSlots();

protected slots:
    void onDeleteBtnClicked();
    void onEditBtnClicked();
    void onUpdateText();

public:
    updateManageWidget(QWidget *parent = nullptr);


};

#endif // UPDATEMANAGEWIDGET_H
