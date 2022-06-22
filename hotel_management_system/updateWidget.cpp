#include "updatewidget.h"

#include <QHBoxLayout>
#include <QDebug>

updateWidget::updateWidget(QWidget *parent):
    QWidget(parent), tabWidget(this), addWidget(NULL), updateMWidget(NULL)
{
    tabWidget.setTabPosition(QTabWidget::North);
    tabWidget.setTabShape(QTabWidget::Rounded);
    tabWidget.setTabsClosable(false);
    addWidget = new addManageWidget(this);
    updateMWidget = new updateManageWidget(this);
    tabWidget.addTab(updateMWidget,"Update");
    tabWidget.addTab(addWidget,"Add");
    tabWidget.setCurrentIndex(0);

    init_operationBx();
    connectSlots();
    vMainLayout.setSpacing(10);
    vMainLayout.addWidget(&tabWidget, 0,0,2,2);
    vMainLayout.addWidget(&operationBx, 2,1,1,1);

    setMinimumSize(650,400);
    setLayout(&vMainLayout);
    setWindowTitle("Manage");
}

void updateWidget::init_operationBx()
{
    QHBoxLayout* layout = new QHBoxLayout();

    layout->addWidget(&confirmBtn);
    layout->addWidget(&cancelBtn);
    confirmBtn.setText("Confirm");
    cancelBtn.setText("Cancel");
    confirmBtn.setFixedHeight(30);
    cancelBtn.setFixedHeight(30);

    operationBx.setMaximumHeight(160);
    operationBx.setLayout(layout);
    operationBx.setStyleSheet("QGroupBox{border:none}");
}

void updateWidget::connectSlots()
{
    connect(&confirmBtn, SIGNAL(clicked(bool)), this, SLOT(onConfirmBtnClicked()));
    connect(&cancelBtn, SIGNAL(clicked(bool)), this, SLOT(onCancelBtnClicked()));
}

void updateWidget::onConfirmBtnClicked()
{
    close();
}

void updateWidget::onCancelBtnClicked()
{
    close();
}
