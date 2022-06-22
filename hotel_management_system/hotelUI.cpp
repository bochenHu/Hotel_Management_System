#include "hotelMainWin.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QDateTime>
#include <QRegExpValidator>
#include <QRegExp>
#include <QDebug>

#include "roomservice.h"

hotelMainWin::hotelMainWin(QWidget *parent)
    : QWidget(parent)
{
    basic_setter();
}

void hotelMainWin::basic_setter()
{
    init_searchBx();
    init_tableBx();
    init_infoBx();
    connectSlots();

    vMainLayout.setSpacing(10);
    vMainLayout.addWidget(&searchBox);
    vMainLayout.addWidget(&tableBox);
    vMainLayout.addWidget(&infoBox);

    setWindowTitle(QString("Hotel Management System"));
    resize(1220,800);
    setMinimumSize(1220,800);
    setLayout(&vMainLayout);
    setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
}

void hotelMainWin::init_searchBx()
{
    QGridLayout* layout = new QGridLayout();

    layout->setSpacing(10);
    layout->addWidget(&room_id_Label,0,0,1,1);
    layout->addWidget(&room_id_Edit,0,1,1,3);
    layout->addWidget(&room_type_Label,0,4,1,1);
    layout->addWidget(&room_type_CbBx,0,5,1,3);
    layout->addWidget(&customer_id_Label,0,8,1,1);
    layout->addWidget(&customer_id_Edit,0,9,1,3);
    room_id_Label.setText(" Room ID:");
    room_type_Label.setText(" Room Type:");
    customer_id_Label.setText(" Customer ID:");
    room_type_CbBx.addItem(QString("--NONE--"));
    room_type_CbBx.addItem(QString("Single Room"));
    room_type_CbBx.addItem(QString("Double Room"));
    room_type_CbBx.addItem(QString("Triple Room"));
    room_type_CbBx.addItem(QString("VIP Room"));
    room_id_Edit.setFixedHeight(23);
    room_type_CbBx.setFixedHeight(23);
    customer_id_Edit.setFixedHeight(23);

    QRegExpValidator* validator = new QRegExpValidator(QRegExp("^[0-9]+$"));
    room_id_Edit.setValidator(validator);
    room_id_Edit.setPlaceholderText("Please enter a room id");
    QRegExpValidator* validator_cust = new QRegExpValidator(QRegExp("^[0-9]+$"));
    customer_id_Edit.setValidator(validator_cust);
    customer_id_Edit.setPlaceholderText("Please enter a customers id");

    layout->addWidget(&priceLabel,1,0,1,1);
    layout->addWidget(&priceEdit,1,1,1,3);
    layout->addWidget(&toLabel,1,4,1,1);
    layout->addWidget(&toEdit,1,5,1,3);
    layout->addWidget(&statusLabel,1,8,1,1);
    layout->addWidget(&statusCbBx,1,9,1,3);
    priceLabel.setText(" Price from:");
    toLabel.setText(" To:");
    statusLabel.setText(" Status:");
    statusCbBx.addItem(QString("--NONE--"));
    statusCbBx.addItem(QString("Empty"));
    statusCbBx.addItem(QString("Checked"));
    priceEdit.setFixedHeight(23);
    toEdit.setFixedHeight(23);
    statusCbBx.setFixedHeight(23);

    QRegExpValidator* validator_priceFrom = new QRegExpValidator(QRegExp("^[0-9]+$"));
    priceEdit.setValidator(validator_priceFrom);
    priceEdit.setPlaceholderText("Please enter a minimum price");
    QRegExpValidator* validator_priceTo = new QRegExpValidator(QRegExp("^[0-9]+$"));
    toEdit.setValidator(validator_priceTo);
    toEdit.setPlaceholderText("Please enter a maximum price");


    layout->addWidget(&inDateLabel,2,0,1,1);
    layout->addWidget(&in_date,2,1,1,3);
    layout->addWidget(&outDateLabel,2,4,1,1);
    layout->addWidget(&out_date,2,5,1,3);

    layout->addWidget(&searchBtn,3,9,1,3);
    inDateLabel.setText(" Date from:");
    outDateLabel.setText(" To:");
    searchBtn.setText("Search");
    in_date.setFixedHeight(23);
    out_date.setFixedHeight(23);
    searchBtn.setFixedHeight(30);
    in_date.setCalendarPopup(true);
    in_date.setDateTime(QDateTime(QDate::currentDate(),QTime::currentTime()));
    out_date.setCalendarPopup(true);
    out_date.setDateTime(QDateTime(QDate::currentDate(),QTime::currentTime()));

    searchBox.setMaximumHeight(160);
    searchBox.setLayout(layout);
    searchBox.setTitle("Search");
}

void hotelMainWin::init_tableBx()
{
    QVBoxLayout* layout = new QVBoxLayout();

    init_Model();
    layout->setSpacing(10);
    layout->addWidget(&tableView);

    tableView.setModel(&standardItemModel);
    tableView.setItemDelegate(&custDelegate);
    tableView.setColumnWidth(4,180);
    tableView.setColumnWidth(5,180);

    tableBox.setLayout(layout);
    tableBox.setTitle("Room information");
}

void hotelMainWin::init_Model()
{
    //use roomservice to return all data
    QList<room> results = (m_authority == "super") ? roomService::selectAllRooms() : roomService::selectRoomsByManagerID(m_managerID);
    //update table view
    updateTableView(results);
}

void hotelMainWin::init_infoBx()
{
    QGridLayout* layout = new QGridLayout();

    layout->setSpacing(10);
    layout->addWidget(&managerLabel,0,0,1,3);
    layout->addWidget(&rightLabel,1,0,1,3);
    layout->addWidget(&writeBtn,1,3);
    layout->addWidget(&closeBtn,1,4);
    managerLabel.setText("Manager: Dan Lee");
    rightLabel.setText("Authority: Super manager");
    writeBtn.setText("Manage");
    closeBtn.setText("Close");
    writeBtn.setFixedHeight(30);
    closeBtn.setFixedHeight(30);

    infoBox.setMaximumHeight(100);
    infoBox.setLayout(layout);
    infoBox.setTitle("Management & Operation");
}

void hotelMainWin::connectSlots()
{
    connect(&closeBtn,SIGNAL(clicked(bool)),this,SLOT(onCancelBtnClicked()));
    connect(&searchBtn,SIGNAL(clicked(bool)),this,SLOT(onSearchBtnClicked()));
    connect(custDelegate.getCheckInDialog(), SIGNAL(accepted()), this, SLOT(updateTable()));
    connect(custDelegate.getDetailDialog(), SIGNAL(accepted()), this, SLOT(updateTable()));
    connect(&writeBtn, SIGNAL(clicked(bool)), this, SLOT(onManageBtnClicked()));
}

hotelMainWin::~hotelMainWin()
{
}
