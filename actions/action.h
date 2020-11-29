#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include "ActionsType.h"
#include "controllers/uicontroller.h"
//#include "controllers/sessioncontroller.h"

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
	Action(int type, QList<int> nextActions = QList<int>(), int enterAction = ActionType::NONE, int cancelAction = ActionType::NONE);

	const QString formatMessage(std::vector<QString> params);
	const QString formatHint(std::vector<QString> params);

	virtual void setupForUI(UIController* uc, SessionController* sc) = 0;
	void setupUI(UIController* uc, SessionController* sc);

	virtual void beforeAction() = 0;
	virtual void actionPerformed(UIActionType actionType, const QString& param = "") = 0;
	virtual void afterAction() = 0;

	int getCancelAction();
	int getEnterAction();

	bool isPinRestricted();


protected:
	//Action() = delete;

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
	int _cancelAction; // if Cancel pressed
	int _enterAction; // if Enter pressed
	QList<int> _nextActions; // screen buttons pressed

	QString formatString(QString& needle, std::vector<QString> params);
};


#endif // ACTION_H
