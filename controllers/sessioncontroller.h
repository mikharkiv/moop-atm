#ifndef SESSIONCONTROLLER_H
#define SESSIONCONTROLLER_H

#include <QObject>
#include "actions/actions.h"
#include "uicontroller.h"

class ATM;
class SessionController : public QObject
{
	Q_OBJECT

	friend class Action;

public:
	SessionController(UIController* uc, ATM* atm);
	~SessionController();

	void setupForAction(Action* a);
	const QString getCurrentCard();

	bool checkPin(const QString& pin);
	bool checkCardExpired(const QString& card);
	bool checkCardExists(const QString& card);
	bool checkCardBlocked(const QString& card);
	bool hasEnoughMoney(int sum);
	bool canGiveSum(int sum);
	int getBalance();
	const QString changePIN();

	const QString createCard(const QString& card);
	void blockCard(const QString& card);
	void unblockCard(const QString& card);
	void addBanknotes(const QMap<int,int>& banknotes);
	void addBalance(int sum);
	void giveCash(int sum);
	void transferMoney(int sum, const QString& card);

	void reset(bool toMode);
	void placeToMemory(const QString& data);
	const QString takeFromMemory();

public slots:
	void onTOMode();
	void onInput(QString& input);
	void onMoneyInsert(QMap<int,int>& money);
	void onCardChosen(QString& cardNumber);
	void onCancelClicked();
	void onActionClicked(int id);
	void showReceipt(const QString& message);

private:
	UIController* _uc;
	Action* _currAction;
	ATM* _atm;
	QString _toPin;

	enum States : int {
		IDLE,
		PIN_CHECKING,
		PIN_WRONG,
		TO_PIN_CHECKING,
		TO_PIN_WRONG,
		TO_IDLE
	};

	States _state;
	QString _currCard;
	int _currPinAttempts;
	int _maxPinAttempts;
	QList<QString> _memory;

	void connectUI();
	void providePinChecking();
};

#endif // SESSIONCONTROLLER_H
