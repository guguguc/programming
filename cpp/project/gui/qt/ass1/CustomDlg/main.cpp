#include "customdlg.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString strNumber("17630053430");
    CustomDlg w(strNumber);
    w.setMask(0, 1);
    w.show();
    return a.exec();
}
