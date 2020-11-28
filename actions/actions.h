#ifndef ACTIONS_H
#define ACTIONS_H

#include "action.h"


class Actions
{
public:
	Actions();
};

class TestAction : public Action {
	// Action interface
public:
	TestAction();
	~TestAction();

	void beforeAction();
	void actionPerformed(int type, QString &input);
	void afterAction();

	// Action interface
public:
	void setupForUI(UIController *uc, SessionController *sc);
	void actionPerformed(UIActionType actionType, const QString &param);
};

#endif // ACTIONS_H
