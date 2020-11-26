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
	delete ui;
}

void ReceiptWindow::setReceiptText(const QStringList &receiptText) {
	ui->receiptTextEdit->setText(receiptText.join("\n"));
}

void ReceiptWindow::on_okButton_clicked()
{
	close();
}
