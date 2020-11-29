#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include "ActionsType.h"
#include "controllers/uicontroller.h"

enum UIActionType : int {
	CANCELED,
	INPUT,
	TO_MODE,
	CARD_INSERTED,
	MONEY_INSERTED,
	ACTION_CLICKED
};

// forward declaration
class UIController;
class SessionController;
class Action
{
public:
	Action(int type);

	void setupForUI(UIController* uc, SessionController* sc);
	virtual void beforeAction();
	virtual void actionPerformed(UIActionType actionType, const QString& param = "") = 0;

	bool isPinRestricted();

protected:
	bool _canType;
	bool _canCancel;
	bool _canInsertMoney;
	bool _canInsertCard;
	bool _canEnterTO;
	bool _isPinRestricted;

	QList<QString> _actionsLabels;
	QString _receiptMessage;
	QString _message;
	QString _typingHint;
	UIController* _uc;
	SessionController* _sc;

	int _type;
};


#endif // ACTION_H
