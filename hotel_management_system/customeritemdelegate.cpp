#include "customeritemdelegate.h"
#include <QComboBox>
#include <QMouseEvent>
#include <QApplication>
#include <QRect>
#include <QMessageBox>
#include <QChar>
#include <QDebug>

#include "roomservice.h"
#include "customerservice.h"
customerItemDelegate::customerItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{

}

void customerItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //Draw check in and check out btn
    if( (index.data().toString() == "check out") || (index.data().toString() == "check in") )
    {
        QStyleOptionButton checkBoxStyle;
        int width = option.rect.width();
        int height = option.rect.height();
        int x = option.rect.x();
        int y = option.rect.y();

        checkBoxStyle.state = QStyle::State_Enabled;
        checkBoxStyle.rect = QRect(int(x+width/16.0), int(y+height/16.0), int(7.0* width/8.0), int(7.0* height/8.0));
        checkBoxStyle.text = index.data().toString() == "check out" ? "Check Out" : "Check In";

        QApplication::style()->drawControl(QStyle::CE_PushButton, &checkBoxStyle, painter);
    }
    else if( (index.data().toString() == "1") || (index.data().toString() == "0") )// Draw detail btn
    {
        QStyleOptionButton checkBoxStyle;
        int width = option.rect.width();
        int height = option.rect.height();
        int x = option.rect.x();
        int y = option.rect.y();

        checkBoxStyle.state = (index.data().toString() == "1") ? QStyle::State_Enabled : QStyle::State_None;
        checkBoxStyle.rect = QRect(int(x+width/16.0), int(y+height/16.0), int(7.0* width/8.0), int(7.0* height/8.0));
        checkBoxStyle.text = "Detail";

        QApplication::style()->drawControl(QStyle::CE_PushButton, &checkBoxStyle, painter);
    }
    else// paint delegate
    {
        QItemDelegate::paint(painter, option, index);
    }
}

bool customerItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    bool ret = true;

    if( (index.data().toString() == "check in") )// show checkInDialog
    {
        QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);

        if( (event->type() == QEvent::MouseButtonPress) && option.rect.contains(mouseEvent->pos()) )
        {
            qDebug() << "CHECK_IN Button clicked...";
            QString roomID = model->sibling(index.row(),0,index).data().toString();
            QString roomType = model->sibling(index.row(),1,index).data().toString();
            QString roomPrice = model->sibling(index.row(),2, index).data().toString();
            QString roomStatus = model->sibling(index.row(),3,index).data().toString();

            dialog.setRoomID(roomID);
            dialog.setRoomType(roomType);
            dialog.setRoomPrice(roomPrice);
            dialog.setRoomStatus(roomStatus);
            dialog.exec();
        }
    }
    else if ((index.data().toString() == "check out")) // judge and check-out
    {
        QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);

        if( (event->type() == QEvent::MouseButtonPress) && option.rect.contains(mouseEvent->pos()) )
        {
            QMessageBox msgBx;
            msgBx.setIcon(QMessageBox::Icon::Information);
            msgBx.setWindowTitle("Hint");
            msgBx.setInformativeText("Are you sure you want to check out?");
            msgBx.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBx.setDefaultButton(QMessageBox::Ok);
            msgBx.setFixedSize(219,152);
            msgBx.move(800,400);
            int ret = msgBx.exec();
            if (ret != QMessageBox::Ok) return false;

            qDebug() << "CHECK_OUT Button clicked...";
            QString roomID = model->sibling(index.row(),0,index).data().toString();

            bool isSuccess = roomService::checkOutUpdate(roomID);

            if (isSuccess){
                bool isSuccess = customerService::checkOutDelete(roomID);
                if (isSuccess){
                    QMessageBox::information(&dialog, "Check Out", "Check out successfully.");
                    //send signal to make main window updated
                    dialog.accept();
                }
                else
                {
                    QMessageBox::critical(&dialog, "Error", "Delete customer unsuccessfully.");
                }
            }
            else
            {
                QMessageBox::critical(&dialog, "Error", "Update room unsuccessfully.");
            }
        }
    }
    else if ((index.data().toString() == "1"))// if detail button is available, show detail dialog
    {
        QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);

        if( (event->type() == QEvent::MouseButtonPress) && option.rect.contains(mouseEvent->pos()) )
        {
            QString roomID = model->sibling(index.row(),0,index).data().toString();
            QString roomType = model->sibling(index.row(),1,index).data().toString();
            QString roomPrice = model->sibling(index.row(),2, index).data().toString();
            QString roomStatus = model->sibling(index.row(),3,index).data().toString();
            QString checkInDate = model->sibling(index.row(), 4, index).data().toString().replace(QChar(' '), QChar('T'));
            QString checkOutDate = model->sibling(index.row(), 5, index).data().toString().replace(QChar(' '), QChar('T'));
            QDateTime inDate = QDateTime::fromString(checkInDate, Qt::ISODate);
            QDateTime outDate = QDateTime::fromString(checkOutDate, Qt::ISODate);

            QList<customer> list = customerService::selectCustomersByQuery(roomID);
            if (list.size() == 0)
            {
                QMessageBox::critical(&detailDialog, "Error", "SELECT customer unsuccessfully.");
            }

            QString customerID = list[0].getCustomer_id();
            QString customerName = list[0].getCustomer_name();
            QString phoneNumber = list[0].getPhone_number();
            QString customerAddress = list[0].getCustomer_address();
            QString accountNumber = list[0].getAccount_number();

            detailDialog.setRoomID(roomID);
            detailDialog.setRoomType(roomType);
            detailDialog.setRoomPrice(roomPrice);
            detailDialog.setRoomStatus(roomStatus);
            detailDialog.setInDate(inDate);
            detailDialog.setOutDate(outDate);
            detailDialog.setCustID(customerID);
            detailDialog.setCustName(customerName);
            detailDialog.setPhoneNumber(phoneNumber);
            detailDialog.setCustomerAddress(customerAddress);
            detailDialog.setAccountNumber(accountNumber);
            detailDialog.exec();
        }
    }
    else
    {
        ret = QItemDelegate::editorEvent(event, model, option, index);
    }

    return ret;
}

QDialog *customerItemDelegate::getCheckInDialog()
{
    return &dialog;
}

QDialog *customerItemDelegate::getDetailDialog()
{
    return &detailDialog;
}
