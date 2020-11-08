#include "atmmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ATMMainWindow w;
    w.show();
    return a.exec();
}
