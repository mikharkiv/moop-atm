#ifndef ATM_H
#define ATM_H

#include <QObject>
#include <QMap>
#include "controllers/uicontroller.h"
#include "bank.h"
#include "localmediator.h"

class SessionController;
class ATM : public QObject
{
	Q_OBJECT
public:
	ATM(ATMMainWindow* ui, int id, const QString& location, QMap<int, int> money, QList<QString> knownCards);

	bool cardExists(const QString& card);
	bool isCardBlocked(const QString& card);
	bool isCardExpired(const QString& card);
	int getBalance(const QString& card);
	bool checkPIN(const QString& card, const QString& pin);
	QString changePIN(const QString& card);

	bool canWithdrawSum(size_t sum);
	void withdrawBanknotes(size_t sum);
	void addBanknotes(QMap<int,int> banknotes);

	void addBalance(size_t sum, const QString& card);
	void subtractBalance(size_t sum, const QString& card);


	const QString createCard(const QString& card);
	void blockCard(const QString& card);
	void unblockCard(const QString& card);

private:
	Bank* _bank;
	LocalMediator* _mediator;
	UIController* _uc;
	int _id;
	QString _location;
	QMap<int, int> _money;
	QList<QString> _knownCards;

	SessionController* _sc;

	QMap<int,int> sumToBanknotes(size_t sum);
};

#endif // ATM_H
