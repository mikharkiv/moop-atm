#include "actions.h"
#include "controllers/sessioncontroller.h"
#include "controllers/uicontroller.h"

Actions::Actions()
{

}

TestAction::TestAction() :
	Action(ActionType::CASH_ADD_ADDED)
{

}

TestAction::~TestAction()
{

}

void TestAction::beforeAction()
{
	_uc->printMessage("Test action setted up!");
}

void TestAction::afterAction()
{

}

void TestAction::setupForUI(UIController *uc, SessionController *sc)
{
	_uc = uc;
	_sc = sc;
	beforeAction();
}

void TestAction::actionPerformed(UIActionType actionType, const QString &param)
{
	if (actionType == UIActionType::ACTION_CLICKED)
		_uc->printMessage("Test action works!");
}
