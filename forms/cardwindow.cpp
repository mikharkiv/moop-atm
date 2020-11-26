#include "cardwindow.h"
#include "ui_cardwindow.h"
#include <QRegExpValidator>
#include <QRegExp>

CardWindow::CardWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CardWindow),
	cardsButtons(parent)
{
	ui->setupUi(this);
	ui->cardNumEdit->setValidator(new QRegExpValidator(QRegExp("[0-9\\- ]*")));

	cardsButtons.addButton(ui->exCardOneButton, 0);
	cardsButtons.addButton(ui->exCardTwoButton, 1);
	cardsButtons.addButton(ui->exCardThreeButton, 2);
	cardsButtons.addButton(ui->exCardFourButton, 3);

	setKnownCards(*(new QList<QString>()));

	checkCardNumber();

	connect(&cardsButtons, SIGNAL(buttonClicked(int)), this, SLOT(onKnownCardButtonClicked(int)));
}

CardWindow::~CardWindow()
{
	delete ui;
}

void CardWindow::setKnownCards(QList<QString> &cards)
{
	knownCards = cards;
	while (knownCards.length() > cardsButtons.buttons().length()) knownCards.pop_back();
	for (int i = 0; i < knownCards.length(); ++i) {
		cardsButtons.button(i)->setText(knownCards.at(i));
		cardsButtons.button(i)->setEnabled(true);
	}
	for (int i = knownCards.length(); i < cardsButtons.buttons().length(); ++i)
		cardsButtons.button(i)->setEnabled(false);
}

void CardWindow::setMinCardNumLength(int minLen)
{
	minCardNumLength = minLen;
	checkCardNumber();
}

void CardWindow::setMaxCardNumLength(int maxLen)
{
	maxCardNumLength = maxLen;
	checkCardNumber();
}

void CardWindow::on_okButton_clicked()
{
	// TODO add event dispatching
	close();
}

void CardWindow::on_cancelButton_clicked()
{
	// TODO add event dispatching
	close();
}

void CardWindow::on_cardNumEdit_textChanged(const QString &text)
{
	checkCardNumber();
}

void CardWindow::onKnownCardButtonClicked(int id)
{
	ui->cardNumEdit->setText(knownCards.at(id));
	checkCardNumber();
}

void CardWindow::checkCardNumber()
{
	ui->okButton->setEnabled(ui->cardNumEdit->text().length() > minCardNumLength &&
			ui->cardNumEdit->text().length() < maxCardNumLength);
}
