#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QTabWidget>
#include <QWidget>
#include <QPalette>
#include <QColor>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>

#include "managerservice.h"
#include "addmanagewidget.h"
#include "updatemanagewidget.h"

class updateWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout vMainLayout;

    QTabWidget tabWidget;
    QGroupBox operationBx;

    addManageWidget* addWidget;
    updateManageWidget* updateMWidget;

    QPushButton confirmBtn;
    QPushButton cancelBtn;
private:
    void init_operationBx();
    void connectSlots();

protected slots:
    void onConfirmBtnClicked();
    void onCancelBtnClicked();
public:
    updateWidget(QWidget* parent = NULL);
};

#endif // UPDATEDIALOG_H
