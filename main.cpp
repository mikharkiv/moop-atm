#include "atmmainwindow.h"
#include "bank.h"
#include "controllers/uicontroller.h"
#include "controllers/sessioncontroller.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    Bank bank("bank_db.sqlite");
    bank.top_up("111111", 56);
    auto acc = bank.getAccount("111111");
//    if (acc.status == OK){
//        qDebug() << acc.value.cardNumber() << ' ' << acc.value.balance();
//    }
    QApplication a(argc, argv);
    ATMMainWindow w;
    w.show();
    UIController c(&w);
    SessionController s(&c);
    w.show();
    return a.exec();
}
