#ifndef ACTIONS_H
#define ACTIONS_H

#include "action.h"

class MainMenuAction : public Action {
public:
	MainMenuAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class CardInsertAction : public Action {
public:
	CardInsertAction();
	void beforeAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class CardBlockedAction : public Action {
public:
	CardBlockedAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class CardExpiredAction : public Action {
public:
	CardExpiredAction();
	void beforeAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class UserMenuAction : public Action {
public:
	UserMenuAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class GetCashAction : public Action {
public:
	GetCashAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class NoBanknotesAction : public Action {
public:
	NoBanknotesAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class NoBalanceAction : public Action {
public:
	NoBalanceAction();
	void beforeAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class CashGivenAction : public Action {
public:
	CashGivenAction();
	void beforeAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TopUpBalanceAction : public Action {
public:
	TopUpBalanceAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class BalanceToppedUpAction : public Action {
public:
	BalanceToppedUpAction();
	void beforeAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class MoneyTransferFirstAction : public Action {
public:
	MoneyTransferFirstAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class MoneyTransferSecondAction : public Action {
public:
	MoneyTransferSecondAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class WrongCardAction : public Action {
public:
	WrongCardAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class MoneyTransferedAction : public Action {
public:
	MoneyTransferedAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class BalancePrintedAction : public Action {
public:
	BalancePrintedAction();
	void beforeAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class PinChangedAction : public Action {
public:
	PinChangedAction();
	void beforeAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class WorkFinishedAction : public Action {
public:
	WorkFinishedAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

#endif // ACTIONS_H
