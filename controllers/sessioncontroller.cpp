#include "sessioncontroller.h"
#include <QDebug>

SessionController::SessionController(UIController* c):
	QObject(),
	_uc(c),
	_state(States::IDLE),
	_currPinAttempts(0),
	_maxPinAttempts(3),
	_currCard(""),
	_memory(QList<QString>())
{
	connectUI();
	setupForAction(new MainMenuAction());
}

SessionController::~SessionController() {}

void SessionController::onTOMode() {
	// TODO TO MODE
}

void SessionController::onInput(QString &input)
{
	if (_state == States::PIN_CHECKING) {
		if (checkPin(input)) {
			_state = States::IDLE;
			_currPinAttempts = 0;
			_currAction->setupForUI(_uc, this);
		} else {
			_currPinAttempts += 1;
			if (_currPinAttempts >= _maxPinAttempts) {
				// TODO get card blocked action
				_uc->printMessage("Через перевищення спроб введення ПІН вашу картку заблоковано. Зверніться до співробітника банку");
				_uc->setTypingEnabled(false);
				// TODO card blocking
			} else {
				_uc->printMessage(QString("Введено неправильний ПІН. Залишилось %1 спроб").arg(QString::number(_maxPinAttempts - _currPinAttempts)), QList<QString>(), "Введіть ПІН-код:");
			}
		}
	} else {
		_currAction->actionPerformed(UIActionType::INPUT, input);
	}
}

void SessionController::onMoneyInsert(QMap<int, int> &money)
{
	addBanknotes(money);
	_currAction->actionPerformed(UIActionType::MONEY_INSERTED, "100");
}

void SessionController::onCardChosen(QString &cardNumber)
{
	_currCard = cardNumber; // TODO checkme
	_currAction->actionPerformed(UIActionType::CARD_INSERTED, cardNumber);
}

void SessionController::onCancelClicked()
{
	_currAction->actionPerformed(UIActionType::CANCELED);
}

void SessionController::onActionClicked(int id)
{
	_currAction->actionPerformed(UIActionType::ACTION_CLICKED, QString::number(id));
}

void SessionController::connectUI()
{
	connect(_uc, SIGNAL(onTOModeClicked()), this, SLOT(onTOMode()));
	connect(_uc, SIGNAL(onCancelClicked()), this, SLOT(onCancelClicked()));
	connect(_uc, SIGNAL(onActionClicked(int)), this, SLOT(onActionClicked(int)));
	connect(_uc, SIGNAL(onInput(QString&)), this, SLOT(onInput(QString&)));
	connect(_uc, SIGNAL(onMoneyInserted(QMap<int,int>&)), this, SLOT(onMoneyInsert(QMap<int,int>&)));
	connect(_uc, SIGNAL(onCardChosen(QString&)), this, SLOT(onCardChosen(QString&)));
}

void SessionController::providePinChecking()
{
	_state = States::PIN_CHECKING;
	_uc->setTypingEnabled(true, true);
	_uc->printMessage(QString("Необхідна перевірка ПІН. Залишилось %1 спроби ").arg(QString::number(_maxPinAttempts - _currPinAttempts)), QList<QString>(), "Введіть ПІН-код:");
	_currPinAttempts = 0;
}

bool SessionController::checkPin(const QString &pin)
{
	return pin == "1234"; // TODO
}

bool SessionController::checkCardExpired(const QString &card)
{
	return false;
}

bool SessionController::checkCardExists(const QString &card)
{
	return true;
}

bool SessionController::checkCardBlocked(const QString &card)
{
	return false;
}

bool SessionController::hasEnoughMoney(int sum)
{
	return true;
}

bool SessionController::canGiveSum(int sum)
{
	return true;
}

int SessionController::getBalance()
{
	return 100; // TODO
}

const QString SessionController::changePIN()
{
	return "1234";
}

void SessionController::blockCard(const QString &card)
{
	// TODO
}

void SessionController::addBanknotes(const QMap<int, int> &banknotes)
{
	// TODO
}

void SessionController::addBalance(int sum)
{
	// TODO
}

void SessionController::giveCash(int sum)
{
	// TODO
}

void SessionController::transferMoney(int sum, const QString &card)
{
	// TODO
}

void SessionController::reset()
{
	_memory.clear();
	_currCard = "";
	_state = States::IDLE;
	_currPinAttempts = 0;
	setupForAction(new MainMenuAction());
}

void SessionController::placeToMemory(const QString &data) {
	_memory.append(data);
}

const QString SessionController::takeFromMemory() {
	return _memory.takeLast();
}

const QString SessionController::getCurrentCard()
{
	return _currCard;
}

void SessionController::setupForAction(Action *a)
{
	_currAction = a;
	if (a->isPinRestricted())
		providePinChecking();
	else
		a->setupForUI(_uc, this);
}
