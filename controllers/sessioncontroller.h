#ifndef SESSIONCONTROLLER_H
#define SESSIONCONTROLLER_H

#include <QObject>
#include "actions/actions.h"
#include "uicontroller.h"

class SessionController : public QObject
{
	Q_OBJECT

	friend class Action;

public:
	SessionController(UIController* uc);
	~SessionController();
	void start();

public slots:
	void onTOMode();
	void onInput(QString& input);
	void onMoneyInsert(QMap<int,int>& money);
	void onCardChosen(QString& cardNumber);
	void onCancelClicked();
	void onActionClicked(int id);

private:
	UIController* _uc;
	Action* _currAction;

	void connectUI();
};

#endif // SESSIONCONTROLLER_H
