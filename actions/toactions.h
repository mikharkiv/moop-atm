#ifndef TOACTIONS_H
#define TOACTIONS_H

#include "action.h"


class TOMenuAction : public Action {
public:
	TOMenuAction();
	void beforeAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOMainMenuAction : public Action {
public:
	TOMainMenuAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TONewCardMenuAction : public Action {
public:
	TONewCardMenuAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TONewCardExistsAction : public Action {
public:
	TONewCardExistsAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TONewCardCreatedAction : public Action {
public:
	TONewCardCreatedAction();
	void beforeAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardBlockMenuAction : public Action {
public:
	TOCardBlockMenuAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardBlockNotExistsAction : public Action {
public:
	TOCardBlockNotExistsAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardBlockAlreadyBlockedAction : public Action {
public:
	TOCardBlockAlreadyBlockedAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardBlockBlockedAction : public Action {
public:
	TOCardBlockBlockedAction();
	void beforeAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardBlockExpiredAction : public Action {
public:
	TOCardBlockExpiredAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardUnblockMenuAction : public Action {
public:
	TOCardUnblockMenuAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardUnblockNotBlockedAction : public Action {
public:
	TOCardUnblockNotBlockedAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardUnblockUnblockedAction : public Action {
public:
	TOCardUnblockUnblockedAction();
	void beforeAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOMoneyInsertMenuAction : public Action {
public:
	TOMoneyInsertMenuAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOMoneyInsertInsertedAction : public Action {
public:
	TOMoneyInsertInsertedAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOWorkFinishedAction : public Action {
public:
	TOWorkFinishedAction();
public:
	void actionPerformed(UIActionType actionType, const QString &param);
};

#endif // TOACTIONS_H
