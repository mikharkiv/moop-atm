#include "sessioncontroller.h"
#include <QDebug>

SessionController::SessionController(UIController* c):
	QObject(),
	_uc(c)
{
	connectUI();
	_currAction = new TestAction();
}

SessionController::~SessionController() {

}

void SessionController::onTOMode()
{

}

void SessionController::onInput(QString &input)
{
}

void SessionController::onMoneyInsert(QMap<int, int> &money)
{

}

void SessionController::onCardChosen(QString &cardNumber)
{

}

void SessionController::onCancelClicked()
{

}

void SessionController::onActionClicked(int id)
{
	_currAction->actionPerformed(UIActionType::ACTION_CLICKED, QString::number(id));
}

void SessionController::connectUI()
{
	connect(_uc, SIGNAL(onTOModeClicked()), this, SLOT(onTOMode()));
	connect(_uc, SIGNAL(onCancelClicked()), this, SLOT(onCancelClicked()));
	connect(_uc, SIGNAL(onActionClicked(int)), this, SLOT(onActionClicked(int)));
	connect(_uc, SIGNAL(onInput(QString&)), this, SLOT(onInput(QString&)));
	connect(_uc, SIGNAL(onMoneyInserted(QMap<int,int>&)), this, SLOT(onMoneyInsert(QMap<int,int>&)));
	connect(_uc, SIGNAL(onCardChosen(QString&)), this, SLOT(onCardChosen(QString&)));
}

void SessionController::start()
{
	_currAction->setupForUI(_uc, this);
}
