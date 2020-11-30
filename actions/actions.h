#ifndef ACTIONS_H
#define ACTIONS_H

#include "action.h"

class MainMenuAction : public Action {
public:
	MainMenuAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class CardInsertAction : public Action {
public:
	CardInsertAction();
	void beforeAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class CardBlockedAction : public Action {
public:
	CardBlockedAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class CardExpiredAction : public Action {
public:
	CardExpiredAction();
	void beforeAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class UserMenuAction : public Action {
public:
	UserMenuAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class GetCashAction : public Action {
public:
	GetCashAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class NoBanknotesAction : public Action {
public:
	NoBanknotesAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class NoBalanceAction : public Action {
public:
	NoBalanceAction();
	void beforeAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class CashGivenAction : public Action {
public:
	CashGivenAction();
	void beforeAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TopUpBalanceAction : public Action {
public:
	TopUpBalanceAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class BalanceToppedUpAction : public Action {
public:
	BalanceToppedUpAction();
	void beforeAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class MoneyTransferFirstAction : public Action {
public:
	MoneyTransferFirstAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class MoneyTransferSecondAction : public Action {
public:
	MoneyTransferSecondAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class WrongCardAction : public Action {
public:
	WrongCardAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class MoneyTransferedAction : public Action {
public:
	MoneyTransferedAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class BalancePrintedAction : public Action {
public:
	BalancePrintedAction();
	void beforeAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class PinChangedAction : public Action {
public:
	PinChangedAction();
	void beforeAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class WorkFinishedAction : public Action {
public:
	WorkFinishedAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

#endif // ACTIONS_H
