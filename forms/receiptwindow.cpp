#include "receiptwindow.h"
#include "ui_receiptwindow.h"

ReceiptWindow::ReceiptWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ReceiptWindow)
{
	ui->setupUi(this);
}

ReceiptWindow::~ReceiptWindow()
{
	emit onWindowClosed();
	delete ui;
}

void ReceiptWindow::setReceiptText(const QString &receiptText) {
	ui->receiptTextEdit->setText(receiptText);
}

void ReceiptWindow::on_okButton_clicked()
{
	emit onWindowClosed();
	close();
}
