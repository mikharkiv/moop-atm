#include "sessioncontroller.h"
#include "atm.h"
#include "actions/toactions.h"
#include <QDebug>

SessionController::SessionController(UIController* c, ATM* atm):
	QObject(),
	_atm(atm),
	_uc(c),
	_state(States::IDLE),
	_currPinAttempts(0),
	_maxPinAttempts(3),
	_currCard(""),
	_memory(QList<QString>()),
	_toPin("83765093")
{
	connectUI();
	setupForAction(new MainMenuAction());
}

SessionController::~SessionController() {}

void SessionController::onTOMode() {
	reset(true);
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
				blockCard(_currCard);
				_uc->printMessage("Через перевищення спроб введення ПІН вашу картку заблоковано. Зверніться до співробітника банку", QList<QString>() << "Ок");
				_uc->setTypingEnabled(false);
				_state = States::PIN_WRONG;
			} else {
				_uc->printMessage(QString("Введено неправильний ПІН. Залишилось %1 спроб").arg(QString::number(_maxPinAttempts - _currPinAttempts)), QList<QString>(), "Введіть ПІН-код:");
			}
		}
	} else if (_state == States::TO_PIN_CHECKING) {
		if (checkPin(input)) {
			_state = States::TO_IDLE;
			_currPinAttempts = 0;
			_currAction->setupForUI(_uc, this);
		} else {
			_currPinAttempts += 1;
			if (_currPinAttempts >= _maxPinAttempts) {
				_uc->printMessage("Через перевищення спроб введення ПІН технічного спеціаліста режим заблоковано");
				_uc->setTypingEnabled(false);
			} else {
				_uc->printMessage(QString("Введено неправильний ПІН. Залишилось %1 спроб").arg(QString::number(_maxPinAttempts - _currPinAttempts)), QList<QString>(), "Введіть ПІН-код технічного спеціаліста:");
			}
		}
	} else {
		_currAction->actionPerformed(UIActionType::INPUT, input);
	}
}

void SessionController::onMoneyInsert(QMap<int, int> &money)
{
	addBanknotes(money);
	int res = 0;
	for (int i = 0; i < money.keys().length(); ++i)
		res += money.keys().at(i) * money[money.keys().at(i)];
	_currAction->actionPerformed(UIActionType::MONEY_INSERTED, QString::number(res));
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
	if (_state == States::PIN_WRONG)
		reset(false);
	else
		_currAction->actionPerformed(UIActionType::ACTION_CLICKED, QString::number(id));
}

void SessionController::showReceipt(const QString &message)
{
	QString receiptText ("");
	receiptText = QDateTime::currentDateTime().toString("Дата: dd.MM.yyyy\nЧас: hh:mm:ss\n\n\n");
	receiptText += QString("Банкомат\nНомер: %1\nАдреса: %2\n\n\n").arg(_atm->getId()).arg(_atm->getLocation());
	receiptText += (_state == States::TO_IDLE ? "Режим технічного спеціаліста\n\n\n" : QString("Режим користувача\nНомер картки: %1\n\n\n").arg(_currCard));
	receiptText += message;
	receiptText += "\n\n\nЦЕЙ ЧЕК Є ЮРИДИЧНИМ ДОКУМЕНТОМ";
	_uc->showReceipt(receiptText);
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
	_uc->setTypingEnabled(true, true);
	_uc->setTOModeEnabled(false);
	_uc->setCardInsertionEnabled(false);
	if (_state == States::TO_IDLE) {
		_state = States::TO_PIN_CHECKING;
	_uc->printMessage(QString("Необхідна перевірка ПІН технічного спеціаліста. Залишилось %1 спроби ").arg(QString::number(_maxPinAttempts - _currPinAttempts)), QList<QString>(), "Введіть ПІН-код технічного спеціаліста:");
	} else {
		_state = States::PIN_CHECKING;
		if (!checkCardExists(_currCard)) {
			_state = States::PIN_WRONG;
			_uc->printMessage("Картки не існує", QList<QString>() << "Ок");
		} else {
			_uc->printMessage(QString("Необхідна перевірка ПІН. Залишилось %1 спроби ").arg(QString::number(_maxPinAttempts - _currPinAttempts)), QList<QString>(), "Введіть ПІН-код:");
		}
	}
	_currPinAttempts = 0;
}

bool SessionController::checkPin(const QString &pin)
{
	if (_state == States::TO_PIN_CHECKING)
		return pin == _toPin;
	else
		return _atm->checkPIN(_currCard, pin);
}

bool SessionController::checkCardExpired(const QString &card)
{
	return _atm->isCardExpired(card);
}

bool SessionController::checkCardExists(const QString &card)
{
	return _atm->cardExists(card);
}

bool SessionController::checkCardBlocked(const QString &card)
{
	return _atm->isCardBlocked(card);
}

bool SessionController::hasEnoughMoney(int sum)
{
	return _atm->getBalance(_currCard) >= sum;
}

bool SessionController::canGiveSum(int sum)
{
	return _atm->canWithdrawSum(sum);
}

int SessionController::getBalance()
{
	return _atm->getBalance(_currCard);
}

const QString SessionController::changePIN()
{
	return _atm->changePIN(_currCard);
}

void SessionController::blockCard(const QString &card)
{
	_atm->blockCard(card);
}

void SessionController::unblockCard(const QString &card)
{
	_atm->unblockCard(card);
}

const QString SessionController::createCard(const QString &card)
{
	return _atm->createCard(card);
}

void SessionController::addBanknotes(const QMap<int, int> &banknotes)
{
	_atm->addBanknotes(banknotes);
}

void SessionController::addBalance(int sum)
{
	_atm->addBalance(sum, _currCard);
}

void SessionController::giveCash(int sum)
{
	_atm->withdrawBanknotes(sum);
}

void SessionController::transferMoney(int sum, const QString &card)
{
	_atm->subtractBalance(sum, _currCard);
	_atm->addBalance(sum, card);
}

void SessionController::reset(bool toMode)
{
	_memory.clear();
	_currCard = "";
	_currPinAttempts = 0;
	if (toMode) {
		_state = States::TO_IDLE;
		setupForAction(new TOMenuAction());
	} else {
		_state = States::IDLE;
		setupForAction(new MainMenuAction());
	}
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
