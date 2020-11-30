#ifndef TOACTIONS_H
#define TOACTIONS_H

#include "action.h"


class TOMenuAction : public Action {
public:
	TOMenuAction();
	void beforeAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOMainMenuAction : public Action {
public:
	TOMainMenuAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TONewCardMenuAction : public Action {
public:
	TONewCardMenuAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TONewCardExistsAction : public Action {
public:
	TONewCardExistsAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TONewCardCreatedAction : public Action {
public:
	TONewCardCreatedAction();
	void beforeAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardBlockMenuAction : public Action {
public:
	TOCardBlockMenuAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardBlockNotExistsAction : public Action {
public:
	TOCardBlockNotExistsAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardBlockAlreadyBlockedAction : public Action {
public:
	TOCardBlockAlreadyBlockedAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardBlockBlockedAction : public Action {
public:
	TOCardBlockBlockedAction();
	void beforeAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardBlockExpiredAction : public Action {
public:
	TOCardBlockExpiredAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardUnblockMenuAction : public Action {
public:
	TOCardUnblockMenuAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardUnblockNotBlockedAction : public Action {
public:
	TOCardUnblockNotBlockedAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardUnblockUnblockedAction : public Action {
public:
	TOCardUnblockUnblockedAction();
	void beforeAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOMoneyInsertMenuAction : public Action {
public:
	TOMoneyInsertMenuAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOMoneyInsertInsertedAction : public Action {
public:
	TOMoneyInsertInsertedAction();
	void beforeAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOWorkFinishedAction : public Action {
public:
	TOWorkFinishedAction();
	void actionPerformed(UIActionType actionType, const QString &param);
};

#endif // TOACTIONS_H
