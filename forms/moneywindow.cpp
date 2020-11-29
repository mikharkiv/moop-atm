#include "moneywindow.h"
#include "ui_moneywindow.h"

MoneyWindow::MoneyWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MoneyWindow),
	banknotes(QMap<int, int>()),
	insertButtons(parent),
	insertedLabels(QList<QLabel*>()),
	_butvals(new int[10]{1,2,5,10,20,50,100,200,500,1000})
{
	ui->setupUi(this);
	ui->okButton->setEnabled(false);

	banknotes.insert(1, 0);
	banknotes.insert(2, 0);
	banknotes.insert(5, 0);
	banknotes.insert(10, 0);
	banknotes.insert(20, 0);
	banknotes.insert(50, 0);
	banknotes.insert(100, 0);
	banknotes.insert(200, 0);
	banknotes.insert(500, 0);
	banknotes.insert(1000, 0);

	insertButtons.addButton(ui->oneButton, 0);
	insertButtons.addButton(ui->twoButton, 1);
	insertButtons.addButton(ui->fiveButton, 2);
	insertButtons.addButton(ui->tenButton, 3);
	insertButtons.addButton(ui->twentyButton, 4);
	insertButtons.addButton(ui->fiftyButton, 5);
	insertButtons.addButton(ui->hButton, 6);
	insertButtons.addButton(ui->twohButton, 7);
	insertButtons.addButton(ui->fivehButton, 8);
	insertButtons.addButton(ui->thousandButton, 9);

	insertedLabels.append(ui->oneCountLabel);
	insertedLabels.append(ui->twoCountLabel);
	insertedLabels.append(ui->fiveCountLabel);
	insertedLabels.append(ui->tenCountLabel);
	insertedLabels.append(ui->twentyCountLabel);
	insertedLabels.append(ui->fiftyCountLabel);
	insertedLabels.append(ui->hCountLabel);
	insertedLabels.append(ui->twohCountLabel);
	insertedLabels.append(ui->fivehCountLabel);
	insertedLabels.append(ui->thousandCountLabel);

	connect(&insertButtons, SIGNAL(buttonClicked(int)), this, SLOT(onInsertButtonClicked(int)));

	checkBanknotesInserted();
}

MoneyWindow::~MoneyWindow()
{
	emit onWindowClosed();
	delete ui;
}

void MoneyWindow::onInsertButtonClicked(int id) {
	banknotes[_butvals[id]] += 1;
	insertedLabels.at(id)->setText(QString::number(banknotes[_butvals[id]]));
	checkBanknotesInserted();
}

void MoneyWindow::checkBanknotesInserted()
{
	int countZero = 0;
	for (int i = 0; i < banknotes.keys().length(); ++i) {
		if (banknotes[i] == 0) ++countZero;
	}
	if (countZero == banknotes.keys().length())
		ui->okButton->setEnabled(false);
	else
		ui->okButton->setEnabled(true);
}

void MoneyWindow::on_cancelButton_clicked()
{
	emit onWindowClosed();
	close();
}

void MoneyWindow::on_okButton_clicked()
{
	emit onMoneyInserted(banknotes);
	close();
}
