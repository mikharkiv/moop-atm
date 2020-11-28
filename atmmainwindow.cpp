#include "atmmainwindow.h"
#include "ui_atmmainwindow.h"
#include "forms/receiptwindow.h"
#include "forms/moneywindow.h"
#include "forms/cardwindow.h"

#include <QFontMetrics>
#include "algorithm"

ATMMainWindow::ATMMainWindow(QWidget *parent)
    : QMainWindow(parent)
	, ui(new Ui::ATMMainWindow),
	  actionsButtons(parent),
	  keyboardButtons(parent)
{
	ui->setupUi(this);

	actionsButtons.addButton(ui->actionOneButton, 0);
	actionsButtons.addButton(ui->actionTwoButton, 1);
	actionsButtons.addButton(ui->actionThreeButton, 2);
	actionsButtons.addButton(ui->actionFourButton, 3);
	actionsButtons.addButton(ui->actionFiveButton, 4);
	actionsButtons.addButton(ui->actionSixButton, 5);
	actionsButtons.addButton(ui->actionSevenButton, 6);
	actionsButtons.addButton(ui->actionEightButton, 7);

	keyboardButtons.addButton(ui->zeroKeybButton, 0);
	keyboardButtons.addButton(ui->oneKeybButton, 1);
	keyboardButtons.addButton(ui->twoKeybButton, 2);
	keyboardButtons.addButton(ui->threeKeybButton, 3);
	keyboardButtons.addButton(ui->fourKeybButton, 4);
	keyboardButtons.addButton(ui->fiveKeybButton, 5);
	keyboardButtons.addButton(ui->sixKeybButton, 6);
	keyboardButtons.addButton(ui->sevenKeybButton, 7);
	keyboardButtons.addButton(ui->eightKeybButton, 8);
	keyboardButtons.addButton(ui->nineKeybButton, 9);

	connect(&actionsButtons, SIGNAL(buttonClicked(int)), this, SLOT(onActionButtonClicked(int)));
	connect(&keyboardButtons, SIGNAL(buttonClicked(int)), this, SLOT(onKeybButtonClicked(int)));
}

ATMMainWindow::~ATMMainWindow()
{
	delete ui;
}

void ATMMainWindow::setCanCardInsert(bool value)
{
	canCardInsert = value;
	ui->insertCardButton->setEnabled(canCardInsert);
}

void ATMMainWindow::setCanCardEject(bool value)
{
	canCardEject = value;
	ui->ejectCardButton->setEnabled(canTOMode);
}

void ATMMainWindow::setCanTOMode(bool value)
{
	canTOMode = value;
	ui->techModeButton->setEnabled(canTOMode);
}

void ATMMainWindow::setCanMoneyInsert(bool value)
{
	canMoneyInsert = value;
	ui->insertMoneyButton->setEnabled(canMoneyInsert);
}

void ATMMainWindow::setCanType(bool value)
{
	canType = value;
	QListIterator<QAbstractButton*> i(keyboardButtons.buttons());
	while (i.hasNext())
		i.next()->setEnabled(canType);
	ui->backspKeybButton->setEnabled(canType);
	ui->enterKeybButton->setEnabled(canType);
}

void ATMMainWindow::setCanCancel(bool value)
{
	canCancel = value;
	ui->cancelKeybButton->setEnabled(canCancel);
}

void ATMMainWindow::setDisplayText(const QString &message, const QList<QString> &actionsTexts, const QString &typingHint, const QString &currInput)
{
	/* The main idea: fit text in TextEdit in a special way, that action labels will be next to the action
	*  buttons, and display message will be in the rest of the space
	*/
	// setup defaults
	QFontMetrics metrics(ui->displayTextEdit->font());
	QString leftActionsBegin = " > ";
	QString rightActionsBegin = " < ";
	QString actionsMiddleSpacer = " | ";
	QString result("");
	// calculating max values
	int actionsCount = 8;
	int actionsRows = 2 * (actionsCount / 2) + 2; // 2 * actionsCount + topGap
	int charsPerRow = ui->displayTextEdit->width() / metrics.averageCharWidth() - 1; // Besause of monospaced font
	int totalRows = ui->displayTextEdit->height() / metrics.height();
	int maxActionLength = (charsPerRow - leftActionsBegin.length() - rightActionsBegin.length() -
			(actionsMiddleSpacer.length() + actionsMiddleSpacer.length() % 2 * 2)) / 2;
	int maxMessageRows = totalRows - actionsRows - 3; // 1 line gap, 1 for type, 1 for hint

	// cut our input message string
	// code catches \n's and max length, therefore so weird
	QString msgCopy = message;
	QString curIterated = "";
	QList<QString> msgSplitted = QList<QString>();
	while (!msgCopy.isEmpty()) {
		QChar c = msgCopy.at(0);
		msgCopy = msgCopy.mid(1, msgCopy.length() - 1);
		if (c != '\n') curIterated += c;
		if (c == '\n' || curIterated.length() >= charsPerRow) {
			msgSplitted.append(curIterated);
			curIterated = "";
		}
	}
	if (!curIterated.isEmpty()) msgSplitted.append(curIterated); // don't forget about last line!
	for (int i = 0; i < (std::min(msgSplitted.length(), maxMessageRows)); ++i)
		result += msgSplitted.at(i) + "\n";
	result = result.mid(0, result.length() - 2); // remove last \n
	int messageRows = message.length() / charsPerRow + 1;


	for (int i = 0; i < (maxMessageRows - messageRows); ++i)
		result += "\n";
	if (canType)
		result += "\n" + typingHint + "\n" + currInput + "\n\n"; // TODO save position to type at
	else
		result += "\n\n\n\n\n";
	QList<QString> resActionsTexts = QList<QString>();
	for (int i = 0; i < actionsCount; ++i) {
		bool isLeftAction = (i < actionsCount / 2);
		QString currActText = (isLeftAction ? leftActionsBegin : actionsMiddleSpacer);
		QString actLbl;
		if (actionsTexts.length() > i) {
			actLbl = actionsTexts.at(i);
			if (actLbl.length() > maxActionLength) actLbl = actLbl.mid(0, maxActionLength); // cut if too big
		}
		if (isLeftAction) currActText += actLbl; // add our line
		// then add spaces for spacing
		for (int j = 0; j < maxActionLength - actLbl.length(); ++j)
			currActText += " ";
		if (!isLeftAction) {
			currActText += actLbl; // add our line after spacing if right
			currActText += rightActionsBegin;
		}
		resActionsTexts.append(currActText);
	}
	int halfsize = resActionsTexts.length() / 2;
	for (int i = 0; i < resActionsTexts.length() / 2; ++i) {
		result += resActionsTexts.at(i) + resActionsTexts.at(i + halfsize) + "\n\n";
	}
	result = result.mid(0, result.length() - 3); // remove two last \n

	ui->displayTextEdit->setText(result);
}

void ATMMainWindow::on_insertCardButton_clicked()
{
	emit onMoneyInsertClicled();
}

void ATMMainWindow::on_insertMoneyButton_clicked()
{
	emit onMoneyInsertClicled();
}

void ATMMainWindow::onKeybButtonClicked(int id)
{
	emit onKeybButtonClicked(id);
}

void ATMMainWindow::onActionButtonClicked(int id)
{
	emit onActionButtonClicked(id);
}


