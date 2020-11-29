#include "action.h"

Action::Action(int type, QList<int> nextActions, int enterAction, int cancelAction):
	_type(type),
	_canType(false),
	_canCancel(false),
	_canInsertMoney(false),
	_canInsertCard(false),
	_canEnterTO(false),
	_isPinRestricted(false),
	_actionsLabels(QList<QString>()),
	_receiptMessage(""),
	_message(""),
	_typingHint(""),
	_enterAction(enterAction),
	_cancelAction(cancelAction),
	_nextActions(nextActions),
	_uc(nullptr),
	_sc(nullptr)
{

}

const QString Action::formatMessage(std::vector<QString> params)
{
	return formatString(_message, params);
}

const QString Action::formatHint(std::vector<QString> params)
{
	return formatString(_typingHint, params);
}

void Action::setupUI(UIController *uc, SessionController *sc)
{
	_uc = uc;
	_sc = sc;

	_uc->setMoneyInsertionEnabled(_canInsertMoney);
	_uc->setCardInsertionEnabled(_canInsertCard);
	_uc->setTOModeEnabled(_canEnterTO);
	_uc->setTypingEnabled(_canType);
	_uc->setCancelingEnabled(_canCancel);
}

int Action::getCancelAction()
{
	return _cancelAction;
}

int Action::getEnterAction()
{
	return _enterAction;
}

bool Action::isPinRestricted()
{
	return _isPinRestricted;
}

QString Action::formatString(QString &needle, std::vector<QString> params)
{
	QString nc = needle;
	for (size_t i = 0; i < params.size(); ++i) {
		nc = needle.arg(params[i]);
	}
	return nc;
}

