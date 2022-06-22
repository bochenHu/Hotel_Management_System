#include "hotelMainWin.h"
#include <QDateTime>
#include <QDebug>
#include <QChar>

#include "updatemanagewidget.h"
#include "addmanagewidget.h"
#include "updatewidget.h"


void hotelMainWin::onSearchBtnClicked()
{
    //get Info from controls
    QString roomID = room_id_Edit.text();
    QString roomType = room_type_CbBx.currentText() == "--NONE--" ? "" : room_type_CbBx.currentText();
    QString customerID = customer_id_Edit.text();
    QString priceFrom = priceEdit.text();
    QString priceTo = toEdit.text();
    QString status = statusCbBx.currentText() == "--NONE--" ? "" : statusCbBx.currentText();
    QString inDate = in_date.dateTime().toString(Qt::ISODate).replace(QChar('T'), QChar(' '));;
    QString outDate = out_date.dateTime().toString(Qt::ISODate).replace(QChar('T'), QChar(' '));

    //get data from databases
    QList<room> results = roomService::selectRoomsByQuery(roomID, roomType, customerID, priceFrom,
                                                          priceTo, status, inDate, outDate, m_authority, m_managerID);
    //update the table
    updateTableView(results);
}

void hotelMainWin::updateTable()
{
    qDebug() << "updateTable...";
    init_Model();
}

void hotelMainWin::updateTableView(QList<room> results)
{
    standardItemModel.clear();
    QStandardItem* root = standardItemModel.invisibleRootItem();

    //set title for the table
    QStandardItem* item_Titles = new QStandardItem[8];
    QString titles[8] = {"Room ID","Room Type","Price","Status","Check-in Date","Check-out Date","Check","Details"};
    for (int i = 0; i < 8; i++){
        item_Titles[i].setData(titles[i], Qt::DisplayRole);
        standardItemModel.setHorizontalHeaderItem(i, item_Titles+i);
    }

    //set content for the table
    for (int j = 0; j < results.size(); j++)
    {

        QStandardItem* items = new QStandardItem[8];
        QString data[8] = {};
        data[0] = QString::number(results[j].getRoom_id());
        data[1] = results[j].getRoom_type();
        data[2] = "$" + QString::number(results[j].getRoom_price());
        data[3] = results[j].getRoom_status();
        data[4] = results[j].getCheck_in_date() == "" ? "NULL" : results[j].getCheck_in_date().replace(QChar('T'), QChar(' '));
        data[5] = results[j].getCheck_out_date() == "" ? "NULL" : results[j].getCheck_out_date().replace(QChar('T'), QChar(' '));
        data[6] = data[3] == "Empty" ? "check in" : "check out";
        data[7] = data[3] == "Empty" ? "0" : "1";
        for (int i = 0; i < 8; i++){
            items[i].setData(data[i], Qt::DisplayRole);

            items[i].setTextAlignment(Qt::AlignCenter);
            items[i].setEditable(false);
            items[i].setSelectable(false);

            root->setChild(j,i,items+i);
        }
    }

    tableView.setColumnWidth(4,180);
    tableView.setColumnWidth(5,180);
}

void hotelMainWin::onManageBtnClicked()
{
    if (m_authority == "super")
    {
        updateWidget* w = new updateWidget(this);
        w->setWindowFlags(Qt::Window);
        w->show();
    }
    else
    {
        QMessageBox::critical(this, "Error", "you do not have permission");
    }
}

void hotelMainWin::onCancelBtnClicked()
{
    close();
}

void hotelMainWin::updateManageBtn()
{
    if (m_authority == "super") writeBtn.setEnabled(true);
    else    writeBtn.setEnabled(false);
}

void hotelMainWin::setManagerName(QString managerName)
{
    managerLabel.setText("Manager: " + managerName);
}

void hotelMainWin::setManagerAuthority(QString authority)
{
    m_authority = authority;
    rightLabel.setText("Authority: " + authority + " manager");
}

void hotelMainWin::getManagerID(QString managerID)
{
    m_managerID = managerID;
}
