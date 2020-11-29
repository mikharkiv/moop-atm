#ifndef ACTIONS_H
#define ACTIONS_H

#include "action.h"

class MainMenuAction : public Action {
	// Action interface
public:
	MainMenuAction();
	~MainMenuAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class CardInsertAction : public Action {
	// Action interface
public:
	CardInsertAction();
	~CardInsertAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class CardBlockedAction : public Action {
	// Action interface
public:
	CardBlockedAction();
	~CardBlockedAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class CardExpiredAction : public Action {
	// Action interface
public:
	CardExpiredAction();
	~CardExpiredAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class UserMenuAction : public Action {
	// Action interface
public:
	UserMenuAction();
	~UserMenuAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class GetCashAction : public Action {
	// Action interface
public:
	GetCashAction();
	~GetCashAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class NoBanknotesAction : public Action {
	// Action interface
public:
	NoBanknotesAction();
	~NoBanknotesAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class NoBalanceAction : public Action {
	// Action interface
public:
	NoBalanceAction();
	~NoBalanceAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class CashGivenAction : public Action {
	// Action interface
public:
	CashGivenAction();
	~CashGivenAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TopUpBalanceAction : public Action {
	// Action interface
public:
	TopUpBalanceAction();
	~TopUpBalanceAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class BalanceToppedUpAction : public Action {
	// Action interface
public:
	BalanceToppedUpAction();
	~BalanceToppedUpAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class MoneyTransferFirstAction : public Action {
	// Action interface
public:
	MoneyTransferFirstAction();
	~MoneyTransferFirstAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class MoneyTransferSecondAction : public Action {
	// Action interface
public:
	MoneyTransferSecondAction();
	~MoneyTransferSecondAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class WrongCardAction : public Action {
	// Action interface
public:
	WrongCardAction();
	~WrongCardAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class MoneyTransferedAction : public Action {
	// Action interface
public:
	MoneyTransferedAction();
	~MoneyTransferedAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class BalancePrintedAction : public Action {
	// Action interface
public:
	BalancePrintedAction();
	~BalancePrintedAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class PinChangedAction : public Action {
	// Action interface
public:
	PinChangedAction();
	~PinChangedAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class WorkFinishedAction : public Action {
	// Action interface
public:
	WorkFinishedAction();
	~WorkFinishedAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

//class TestAction : public Action {
//	// Action interface
//public:
//	TestAction();
//	~TestAction();
//
//	void beforeAction();
//	void actionPerformed(int type, QString &input);
//	void afterAction();
//
//	// Action interface
//public:
//	void setupForUI(UIController *uc, SessionController *sc);
//	void actionPerformed(UIActionType actionType, const QString &param);
//};

#endif // ACTIONS_H
