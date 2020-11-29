#ifndef ATM_H
#define ATM_H

#include <QObject>
#include <QMap>
#include "controllers/uicontroller.h"
#include "controllers/sessioncontroller.h"

class ATM
{
	Q_OBJECT
public:
	ATM(int id, const QString& location, QMap<int, int> money, QList<QString> knownCards);

	bool cardExists(const QString& card);
	bool isCardBlocked(const QString& card);
	bool isCardExpired(const QString& card);
	int getBalance(const QString& card);
	bool checkPIN(const QString& card, const QString& pin);

	bool canWithdrawSum(size_t sum);
	void withdrawBanknotes(size_t sum);
	void addBanknotes(QMap<int,int> banknotes);

	void addBalance(size_t sum, QString& card);
	void subtractBalance(size_t sum, QString& card);


	void blockCard(QString& card);
	void unblockCard(QString& card);

public slots:
	void doModeSwitching(bool toTOMode);

private:
	UIController* _uc;
	int _id;
	QString _location;
	bool _isTOMode;
	QMap<int, int> _money;
	QList<QString> _knownCards;

	SessionController* _sc;
//	TOSessionController* _tsc;

	void start();
	void reset();
	void switchMode(bool toTO);

};

#endif // ATM_H
