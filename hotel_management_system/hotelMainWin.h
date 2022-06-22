#ifndef HOTEL_H
#define HOTEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTableView>
#include <QStandardItemModel>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QString>
#include <QMessageBox>

#include <QList>

#include "roomservice.h"
#include "room.h"

#include "customeritemdelegate.h"


class hotelMainWin : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout vMainLayout;
    QGroupBox searchBox;
    QGroupBox tableBox;
    QGroupBox infoBox;

    QLabel room_id_Label;
    QLineEdit room_id_Edit;
    QLabel room_type_Label;
    QComboBox room_type_CbBx;
    QLabel customer_id_Label;
    QLineEdit customer_id_Edit;
    QLabel priceLabel;
    QLineEdit priceEdit;
    QLabel toLabel;
    QLineEdit toEdit;
    QLabel statusLabel;
    QComboBox statusCbBx;
    QLabel inDateLabel;
    QDateTimeEdit in_date;
    QLabel outDateLabel;
    QDateTimeEdit out_date;
    QPushButton searchBtn;

    QTableView tableView;
    QStandardItemModel standardItemModel;
    customerItemDelegate custDelegate;

    QLabel managerLabel;
    QLabel rightLabel;
    QPushButton writeBtn;
    QPushButton closeBtn;

    QString m_authority;
    QString m_managerID;
private:
    void basic_setter();

    void init_searchBx();
    void init_tableBx();
    void init_infoBx();
    void connectSlots();

    void updateTableView(QList<room> results);
protected slots:
    void onCancelBtnClicked();
    void onSearchBtnClicked();
    void onManageBtnClicked();
    void updateTable();

public:
    hotelMainWin(QWidget *parent = 0);
    void init_Model();
    void updateManageBtn();
    void setManagerName(QString managerName);
    void setManagerAuthority(QString authority);
    void getManagerID(QString managerID);
    ~hotelMainWin();
};

#endif // HOTEL_H
