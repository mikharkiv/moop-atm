#include "atmmainwindow.h"
#include "bank.h"
#include "controllers/uicontroller.h"
#include "controllers/sessioncontroller.h"

#include <QApplication>
#include <QDebug>
#include "atm.h"

int main(int argc, char *argv[])
{
//    Bank bank;
//    bank.top_up("111111", 56);
//    auto acc = bank.getAccount("111111");
//    if (acc.status == OK){
//        qDebug() << acc.value.cardNumber() << ' ' << acc.value.balance();
//    }
    QApplication a(argc, argv);
    ATMMainWindow w;
	w.show();
	ATM atm(&w, 0, "Kyiv", QMap<int,int>(), QList<QString>());
    return a.exec();
}
