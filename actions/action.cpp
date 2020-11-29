#include "action.h"
#include "controllers/uicontroller.h"

Action::Action(int type):
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
	_uc(nullptr),
	_sc(nullptr)
{}

void Action::beforeAction() {
	_uc->printMessage(_message, _actionsLabels, _typingHint);
}

bool Action::isPinRestricted() {
	return _isPinRestricted;
}

void Action::setupForUI(UIController *uc, SessionController *sc) {
	_uc = uc;
	_sc = sc;

	_uc->setMoneyInsertionEnabled(_canInsertMoney);
	_uc->setCardInsertionEnabled(_canInsertCard);
	_uc->setTOModeEnabled(_canEnterTO);
	_uc->setTypingEnabled(_canType);
	_uc->setCancelingEnabled(_canCancel);

	beforeAction();
}
