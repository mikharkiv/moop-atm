#include "uicontroller.h"

#include "atmmainwindow.h"
#include <QObject>

UIController::UIController(ATMMainWindow* mainWindow):
	_mainWindow(mainWindow),
	_receiptWindow(nullptr),
	_moneyWindow(nullptr),
	_cardWindow(nullptr),
	_knownCards(QList<QString>())
{
	connectMainWindow();
}

UIController::~UIController() {
}

void UIController::setKnownCards(QList<QString> &cards)
{
	_knownCards = cards;
}

void UIController::showReceipt(const QString &message)
{
	ReceiptWindow rw(_mainWindow->parentWidget());
	rw.setReceiptText(message);
	_receiptWindow = &rw;

	rw.exec();
}

void UIController::printMessage(const QString &message, const QList<QString> &actions, const QString &typingHint)
{
	_mainWindow->print(message, actions, typingHint);
}

void UIController::showMoneyWindow()
{
	MoneyWindow w(_mainWindow->parentWidget());
	_moneyWindow = &w;
	connectMoneyWindow();

	w.exec();
}

void UIController::showCardWindow(QList<QString>& knownCards)
{
	CardWindow w(_mainWindow->parentWidget());
	w.setMinCardNumLength(0);
	w.setMaxCardNumLength(30);
	w.setKnownCards(knownCards);
	_cardWindow = &w;
	connectCardWindow();

	w.exec();

}

void UIController::setMoneyInsertionEnabled(bool enabled)
{
	_mainWindow->setCanMoneyInsert(enabled);
}

void UIController::setTypingEnabled(bool enabled, bool hidden)
{
	_mainWindow->setCanType(enabled, hidden);
}

void UIController::setCancelingEnabled(bool enabled)
{
	_mainWindow->setCanCancel(enabled);
}

void UIController::setTOModeEnabled(bool enabled)
{
	_mainWindow->setCanTOMode(enabled);
}

void UIController::setCardInsertionEnabled(bool enabled)
{
	_mainWindow->setCanCardInsert(enabled);
}

void UIController::connectMainWindow()
{
	connect(_mainWindow, SIGNAL(onCardInsertClicked()), this, SLOT(onMainWinCardInsertClicked()));
	connect(_mainWindow, SIGNAL(onTOModeClicked()), this, SLOT(onMainWinTOModeClicked()));
	connect(_mainWindow, SIGNAL(onActionButtonClicked(int)), this, SLOT(onMainWinActionButClicked(int)));
	connect(_mainWindow, SIGNAL(onMoneyInsertClicked()), this, SLOT(onMainWinMoneyInsertClicked()));
	connect(_mainWindow, SIGNAL(onCancelClicked()), this, SLOT(onMainWinCancelClicked()));
	connect(_mainWindow, SIGNAL(onInputEntered(QString&)), this, SLOT(onMainWinInputEntered(QString&)));
}

void UIController::connectMoneyWindow()
{
	connect(_moneyWindow, SIGNAL(onMoneyInserted(QMap<int,int>&)), this, SLOT(onMoneyWinMoneyInserted(QMap<int,int>&)));
	connect(_moneyWindow, SIGNAL(onWindowClosed()), this, SLOT(onMoneyWinClosed()));
}

void UIController::connectCardWindow()
{
	connect(_cardWindow, SIGNAL(onCardChosen(QString)), this, SLOT(onCWinCardChosen(QString)));
	connect(_cardWindow, SIGNAL(onWindowClosed()), this, SLOT(onCWinClosed()));

}

void UIController::onMainWinMoneyInsertClicked()
{
	showMoneyWindow();
}

void UIController::onMainWinCardInsertClicked()
{
	showCardWindow(_knownCards);
}

void UIController::onMainWinTOModeClicked()
{
	emit onTOModeClicked();
}

void UIController::onMainWinCancelClicked()
{
	emit onCancelClicked();
}

void UIController::onMainWinActionButClicked(int id)
{
	emit onActionClicked(id);
}

void UIController::onMainWinInputEntered(QString &input)
{
	emit onInput(input);
}

void UIController::onCWinCardChosen(QString cardNum)
{
	emit onCardChosen(cardNum);
}

void UIController::onCWinClosed()
{
	// HAHA that was a joke lol
}

void UIController::onMoneyWinMoneyInserted(QMap<int, int> &money)
{
	emit onMoneyInserted(money);
}

void UIController::onMoneyWinClosed()
{

}
