#include "atmmainwindow.h"
#include "ui_atmmainwindow.h"
#include "forms/receiptwindow.h"
#include "forms/moneywindow.h"
#include "forms/cardwindow.h"

ATMMainWindow::ATMMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ATMMainWindow)
{
	ui->setupUi(this);
}

ATMMainWindow::~ATMMainWindow()
{
    delete ui;
}

// TODO for test
void ATMMainWindow::on_insertCardButton_clicked()
{
	CardWindow w(parentWidget());
	QList<QString> tc;
	tc.append("1111-1111-1111-1111");
	tc.append("222-222-22-2");
	w.setMinCardNumLength(2);
	w.setMaxCardNumLength(10);
	w.setKnownCards(tc);
	w.exec();
}

// TODO for test
void ATMMainWindow::on_insertMoneyButton_clicked()
{
	MoneyWindow w(parentWidget());
	w.exec();
}
