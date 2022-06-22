#include "qlogindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLoginDialog w;
    w.show();

    return a.exec();
}
