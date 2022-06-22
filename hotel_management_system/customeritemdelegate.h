#ifndef CUSTOMERITEMDELEGATE_H
#define CUSTOMERITEMDELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QString>
#include "checkindialog.h"
#include "detaildialog.h"

class customerItemDelegate : public QItemDelegate
{
private:
    checkInDialog dialog;
    detailDialog detailDialog;

public:
    explicit customerItemDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    QDialog* getCheckInDialog();
    QDialog* getDetailDialog();
};

#endif // CUSTOMERITEMDELEGATE_H
