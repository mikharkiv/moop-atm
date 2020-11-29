#ifndef TOACTIONS_H
#define TOACTIONS_H

#include "action.h"


class TOMenuAction : public Action {
	// Action interface
public:
	TOMenuAction();
	~TOMenuAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOMainMenuAction : public Action {
	// Action interface
public:
	TOMainMenuAction();
	~TOMainMenuAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TONewCardMenuAction : public Action {
	// Action interface
public:
	TONewCardMenuAction();
	~TONewCardMenuAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TONewCardExistsAction : public Action {
	// Action interface
public:
	TONewCardExistsAction();
	~TONewCardExistsAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TONewCardCreatedAction : public Action {
	// Action interface
public:
	TONewCardCreatedAction();
	~TONewCardCreatedAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardBlockMenuAction : public Action {
	// Action interface
public:
	TOCardBlockMenuAction();
	~TOCardBlockMenuAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardBlockNotExistsAction : public Action {
	// Action interface
public:
	TOCardBlockNotExistsAction();
	~TOCardBlockNotExistsAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardBlockAlreadyBlockedAction : public Action {
	// Action interface
public:
	TOCardBlockAlreadyBlockedAction();
	~TOCardBlockAlreadyBlockedAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardBlockBlockedAction : public Action {
	// Action interface
public:
	TOCardBlockBlockedAction();
	~TOCardBlockBlockedAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardBlockExpiredAction : public Action {
	// Action interface
public:
	TOCardBlockExpiredAction();
	~TOCardBlockExpiredAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardUnblockMenuAction : public Action {
	// Action interface
public:
	TOCardUnblockMenuAction();
	~TOCardUnblockMenuAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardUnblockNotBlockedAction : public Action {
	// Action interface
public:
	TOCardUnblockNotBlockedAction();
	~TOCardUnblockNotBlockedAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOCardUnblockUnblockedAction : public Action {
	// Action interface
public:
	TOCardUnblockUnblockedAction();
	~TOCardUnblockUnblockedAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOMoneyInsertMenuAction : public Action {
	// Action interface
public:
	TOMoneyInsertMenuAction();
	~TOMoneyInsertMenuAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOMoneyInsertInsertedAction : public Action {
	// Action interface
public:
	TOMoneyInsertInsertedAction();
	~TOMoneyInsertInsertedAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

class TOWorkFinishedAction : public Action {
	// Action interface
public:
	TOWorkFinishedAction();
	~TOWorkFinishedAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

#endif // TOACTIONS_H
