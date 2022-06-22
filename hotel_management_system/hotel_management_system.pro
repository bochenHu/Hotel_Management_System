#-------------------------------------------------
#
# Project created by QtCreator 2022-06-13T06:27:03
#
#-------------------------------------------------

QT       += core gui widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hotel_management_system
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    hotelUI.cpp \
    customeritemdelegate.cpp \
    hotel.cpp \
    manager.cpp \
    room.cpp \
    customer.cpp \
    roomservice.cpp \
    sqlservice.cpp \
    hotelslots.cpp \
    checkindialog.cpp \
    customerservice.cpp \
    detaildialog.cpp \
    qlogindialog.cpp \
    managerservice.cpp \
    updatemanagewidget.cpp \
    addmanagewidget.cpp \
    updatewidget.cpp

HEADERS += \
    customeritemdelegate.h \
    hotelMainWin.h \
    hotel.h \
    manager.h \
    room.h \
    customer.h \
    roomservice.h \
    sqlservice.h \
    checkindialog.h \
    customerservice.h \
    detaildialog.h \
    qlogindialog.h \
    managerservice.h \
    updatemanagewidget.h \
    addmanagewidget.h \
    updatewidget.h

RC_FILE = myapp.rc
