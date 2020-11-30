#include "atmmainwindow.h"
#include "bank.h"
#include "controllers/uicontroller.h"
#include "controllers/sessioncontroller.h"

#include <QApplication>
#include <QDebug>
#include "atm.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ATMMainWindow w;
    w.show();

	// money in the ATM
    QMap<int, int> money;
    money[1000] = 1;
    money[500] = 1;
    money[200] = 1;
    money[100] = 2;
    money[20] = 20;
    money[10] = 10;
    money[5] = 2;
    money[2] = 10;

	QList<QString> knowedCards;

    ATM atm(&w, 0, "Kyiv", money, knowedCards);
    return a.exec();
}
