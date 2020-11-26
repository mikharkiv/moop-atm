#include "moneywindow.h"
#include "ui_moneywindow.h"

MoneyWindow::MoneyWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MoneyWindow)
{
	ui->setupUi(this);
}

MoneyWindow::~MoneyWindow()
{
	delete ui;
}
