#include "atm.h"
#include "controllers/sessioncontroller.h"
#include <QRandomGenerator>

ATM::ATM(ATMMainWindow* ui, int id, const QString &location, QMap<int, int> money, QList<QString> knownCards):
	QObject(),
	_id(id),
	_location(location),
	_money(money),
	_knownCards(knownCards),
	_bank(new Bank()),
	_mediator(new LocalMediator(_bank)),
	_uc(new UIController(ui)),
	_sc(new SessionController(_uc, this))
{
	_uc->setKnownCards(_knownCards);
	_sc->reset(false);
}

bool ATM::cardExists(const QString &card)
{
	return _mediator->getAccount(card).status() == OK;
}

bool ATM::isCardBlocked(const QString &card)
{
	BankResponse<Account> br = _mediator->getAccount(card);
	if (br.status() == OK) {
		return br.value().blocked();
	} else return false;
}

bool ATM::isCardExpired(const QString &card)
{
	BankResponse<Account> br = _mediator->getAccount(card);
	if (br.status() == OK) {
		return (br.value().expirationDate() > QDateTime::currentDateTime());
	} else return false;
}

int ATM::getBalance(const QString &card)
{
	BankResponse<Account> br = _mediator->getAccount(card);
	if (br.status() == OK) {
		return br.value().balance();
	} else return 0;
}

bool ATM::checkPIN(const QString &card, const QString &pin)
{
	BankResponse<bool> br = _mediator->checkPin(card, pin);
	if (br.status() == OK) {
		return br.value();
	} else return false;
}

QString ATM::changePIN(const QString &card)
{
	int rand = QRandomGenerator::global()->bounded(10000);
	QString rands = QString::number(rand);
	rands = QString("0").repeated(4 - rands.length()) + rands;
	_mediator->setPin(card, rands);
	return rands;
}

bool ATM::canWithdrawSum(size_t sum)
{

	return true;
}

void ATM::withdrawBanknotes(size_t sum)
{

}

void ATM::addBanknotes(QMap<int, int> banknotes)
{
	for (int i = 0; i < banknotes.keys().length(); ++i) {
		int key = banknotes.keys().at(i);
		if (_money.keys().contains(key))
			_money[key] = _money[key] + banknotes[key];
		else
			_money[key] = banknotes[key];
	}
}

void ATM::addBalance(size_t sum, const QString &card)
{
	_mediator->top_up(card, sum);
}

void ATM::subtractBalance(size_t sum, const QString &card)
{
	_mediator->withdraw(card, sum);
}

const QString ATM::createCard(const QString &card)
{
	int rand = QRandomGenerator::global()->bounded(10000);
	QString rands = QString::number(rand);
	rands = QString("0").repeated(4 - rands.length()) + rands;
	Account a(card, QDateTime::currentDateTime().addYears(1), rands);
	_mediator->createAccount(a);
	return rands;
}

void ATM::blockCard(const QString &card)
{
	_mediator->block(card);
}

void ATM::unblockCard(const QString &card)
{
	_mediator->unblock(card);
}
