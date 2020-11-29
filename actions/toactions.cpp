#include "toactions.h"
#include "controllers/sessioncontroller.h"
#include "controllers/uicontroller.h"


TOMenuAction::TOMenuAction(): Action(ActionType::TO_MENU) {_isPinRestricted = true;}
TOMenuAction::~TOMenuAction() {}
void TOMenuAction::beforeAction() {
	_sc->setupForAction(new TOMainMenuAction());
}
void TOMenuAction::afterAction() {}
void TOMenuAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void TOMenuAction::actionPerformed(UIActionType actionType, const QString &param) {}

TOMainMenuAction::TOMainMenuAction(): Action(ActionType::TO_MAIN_MENU) {
    _message = "Меню технічого спеціаліста.\nВиберіть операцію:";
	_actionsLabels = QList<QString>() << "Створити нову картку" << "Заблокувати картку" << "Розблокувати картку" << "Вийти з режиму ТО";
}
TOMainMenuAction::~TOMainMenuAction() {}
void TOMainMenuAction::beforeAction() {
	_uc->printMessage(_message, _actionsLabels);
}
void TOMainMenuAction::afterAction() {}
void TOMainMenuAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
    beforeAction();
}
void TOMainMenuAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED) {
		int action = param.toInt();
		switch (action) {
			case 0: _sc->setupForAction(new TONewCardMenuAction()); break;
			case 1: _sc->setupForAction(new TOCardBlockMenuAction()); break;
			case 2: _sc->setupForAction(new TOCardUnblockMenuAction()); break;
			case 3: _sc->setupForAction(new TOWorkFinishedAction()); break;
		}
	}
}

TONewCardMenuAction::TONewCardMenuAction(): Action(ActionType::TO_NEW_CARD_MENU) {
    _message = "Введіть номер картки:";
    _canType = true;
}
TONewCardMenuAction::~TONewCardMenuAction() {}
void TONewCardMenuAction::beforeAction() {
    _uc->printMessage(_message);
}
void TONewCardMenuAction::afterAction() {}
void TONewCardMenuAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
    beforeAction();
}
void TONewCardMenuAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::INPUT) {
		if (_sc->checkCardExists(param)) {
			_sc->setupForAction(new TONewCardExistsAction());
		} else {
			_sc->placeToMemory(param);
			_sc->setupForAction(new TONewCardCreatedAction());
		}
	}

}

TONewCardExistsAction::TONewCardExistsAction(): Action(ActionType::TO_NEW_CARD_EXISTS) {
	_message = "Картка вже існує. Спробуйте іншу";
    _actionsLabels = QList<QString>() << "Ок";
}
TONewCardExistsAction::~TONewCardExistsAction() {}
void TONewCardExistsAction::beforeAction() {
    _uc->printMessage(_message, _actionsLabels);
}
void TONewCardExistsAction::afterAction() {}
void TONewCardExistsAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
    beforeAction();
}
void TONewCardExistsAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new TOMainMenuAction());
}

TONewCardCreatedAction::TONewCardCreatedAction(): Action(ActionType::TO_NEW_CARD_CREATED) {
	_message = "Картку успішно створено. ПІН надруковано на чеку";
    _actionsLabels = QList<QString>() << "Ок";
}
TONewCardCreatedAction::~TONewCardCreatedAction() {}
void TONewCardCreatedAction::beforeAction() {
	_uc->showReceipt(QString("ПІН: %1").arg(_sc->createCard(_sc->takeFromMemory())));
    _uc->printMessage(_message, _actionsLabels);
}
void TONewCardCreatedAction::afterAction() {}
void TONewCardCreatedAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
    beforeAction();
}
void TONewCardCreatedAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new TOMainMenuAction());
}

TOCardBlockMenuAction::TOCardBlockMenuAction(): Action(ActionType::TO_CARD_BLOCK_MENU) {
	_message = "Введіть номер картки для блокування";
	_canType = true;
}
TOCardBlockMenuAction::~TOCardBlockMenuAction() {}
void TOCardBlockMenuAction::beforeAction() {
    _uc->printMessage(_message, _actionsLabels);
}
void TOCardBlockMenuAction::afterAction() {}
void TOCardBlockMenuAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
    beforeAction();
}
void TOCardBlockMenuAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::INPUT) {
		if (!_sc->checkCardExists(param)) {
			_sc->setupForAction(new TOCardBlockNotExistsAction());
		} else if (_sc->checkCardExpired(param)) {
			_sc->setupForAction(new TOCardBlockExpiredAction());
		} else if (_sc->checkCardBlocked(param)) {
			_sc->setupForAction(new TOCardBlockAlreadyBlockedAction());
		} else {
			_sc->placeToMemory(param);
			_sc->setupForAction(new TOCardBlockBlockedAction());
		}
	}
}

TOCardBlockNotExistsAction::TOCardBlockNotExistsAction(): Action(ActionType::TO_CARD_BLOCK_NOT_EXISTS) {
	_message = "Картки не існує. Спробуйте іншу";
    _actionsLabels = QList<QString>() << "Ок";
}
TOCardBlockNotExistsAction::~TOCardBlockNotExistsAction() {}
void TOCardBlockNotExistsAction::beforeAction() {
    _uc->printMessage(_message, _actionsLabels);
}
void TOCardBlockNotExistsAction::afterAction() {}
void TOCardBlockNotExistsAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
    beforeAction();
}
void TOCardBlockNotExistsAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new TOMainMenuAction());
}

TOCardBlockAlreadyBlockedAction::TOCardBlockAlreadyBlockedAction(): Action(ActionType::TO_CARD_BLOCK_ALREADY_BLOCKED) {
	_message = "Картка вже заблокована";
    _actionsLabels = QList<QString>() << "Ок";
}
TOCardBlockAlreadyBlockedAction::~TOCardBlockAlreadyBlockedAction() {}
void TOCardBlockAlreadyBlockedAction::beforeAction() {
    _uc->printMessage(_message, _actionsLabels);
}
void TOCardBlockAlreadyBlockedAction::afterAction() {}
void TOCardBlockAlreadyBlockedAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
    beforeAction();
}
void TOCardBlockAlreadyBlockedAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new TOMainMenuAction());
}

TOCardBlockBlockedAction::TOCardBlockBlockedAction(): Action(ActionType::TO_CARD_BLOCK_BLOCKED) {
	_message = "Введену картку успішно заблоковано";
    _actionsLabels = QList<QString>() << "Ок";
}
TOCardBlockBlockedAction::~TOCardBlockBlockedAction() {}
void TOCardBlockBlockedAction::beforeAction() {
    _uc->printMessage(_message, _actionsLabels);
	QString c = _sc->takeFromMemory();
	_sc->blockCard(c);
	_uc->showReceipt(QString("Заблоковано картку: %1").arg(c));
}
void TOCardBlockBlockedAction::afterAction() {}
void TOCardBlockBlockedAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
    beforeAction();
}
void TOCardBlockBlockedAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new TOMainMenuAction());
}

TOCardBlockExpiredAction::TOCardBlockExpiredAction(): Action(ActionType::TO_CARD_BLOCK_EXPIRED) {
	_message = "Термін дії введеної картки сплив. Спробуйте іншу";
    _actionsLabels = QList<QString>() << "Ок";
}
TOCardBlockExpiredAction::~TOCardBlockExpiredAction() {}
void TOCardBlockExpiredAction::beforeAction() {
    _uc->printMessage(_message, _actionsLabels);
}
void TOCardBlockExpiredAction::afterAction() {}
void TOCardBlockExpiredAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
    beforeAction();
}
void TOCardBlockExpiredAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new TOMainMenuAction());
}

TOCardUnblockMenuAction::TOCardUnblockMenuAction(): Action(ActionType::TO_CARD_UNBLOCK_MENU) {
	_message = "Введіть номер картки для розблокування";
	_canType = true;
}
TOCardUnblockMenuAction::~TOCardUnblockMenuAction() {}
void TOCardUnblockMenuAction::beforeAction() {
	_uc->printMessage(_message);
}
void TOCardUnblockMenuAction::afterAction() {}
void TOCardUnblockMenuAction::setupForUI(UIController *uc, SessionController *sc) {
    Action::setupUI(uc, sc);
    beforeAction();
}
void TOCardUnblockMenuAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::INPUT) {
		if (!_sc->checkCardExists(param)) {
			_sc->setupForAction(new TOCardBlockNotExistsAction());
		} else if (_sc->checkCardExpired(param)) {
			_sc->setupForAction(new TOCardBlockExpiredAction());
		} else if (!_sc->checkCardBlocked(param)) {
			_sc->setupForAction(new TOCardUnblockNotBlockedAction());
		} else {
			_sc->placeToMemory(param);
			_sc->setupForAction(new TOCardUnblockUnblockedAction());
		}
	}
}

TOCardUnblockNotBlockedAction::TOCardUnblockNotBlockedAction(): Action(ActionType::TO_CARD_UNBLOCK_NOT_BLOCKED) {
	_message = "Введену картку не заблоковано. Спробуйте іншу";
    _actionsLabels = QList<QString>() << "Ок";
}
TOCardUnblockNotBlockedAction::~TOCardUnblockNotBlockedAction() {}
void TOCardUnblockNotBlockedAction::beforeAction() {
    _uc->printMessage(_message, _actionsLabels);
}
void TOCardUnblockNotBlockedAction::afterAction() {}
void TOCardUnblockNotBlockedAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
    beforeAction();
}
void TOCardUnblockNotBlockedAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new TOMainMenuAction());
}

TOCardUnblockUnblockedAction::TOCardUnblockUnblockedAction(): Action(ActionType::TO_CARD_UNBLOCK_UNBLOCKED) {
	_message = "Введену картку успішно розблоковано";
    _actionsLabels = QList<QString>() << "Ок";
}
TOCardUnblockUnblockedAction::~TOCardUnblockUnblockedAction() {}
void TOCardUnblockUnblockedAction::beforeAction() {
    _uc->printMessage(_message, _actionsLabels);
	QString c = _sc->takeFromMemory();
	_sc->unblockCard(c);
	_uc->showReceipt(QString("Картку розблоковано: %1").arg(c));
}
void TOCardUnblockUnblockedAction::afterAction() {}
void TOCardUnblockUnblockedAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
    beforeAction();
}
void TOCardUnblockUnblockedAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new TOMainMenuAction());
}

TOMoneyInsertMenuAction::TOMoneyInsertMenuAction(): Action(ActionType::TO_MONEY_INSERT_MENU) {
	_message = "Вставте купюри в купюроприймач";
	_canInsertMoney = true;
}
TOMoneyInsertMenuAction::~TOMoneyInsertMenuAction() {}
void TOMoneyInsertMenuAction::beforeAction() {
	_uc->printMessage(_message);
}
void TOMoneyInsertMenuAction::afterAction() {}
void TOMoneyInsertMenuAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
    beforeAction();
}
void TOMoneyInsertMenuAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::MONEY_INSERTED)
		_sc->setupForAction(new TOMoneyInsertInsertedAction());
}

TOMoneyInsertInsertedAction::TOMoneyInsertInsertedAction(): Action(ActionType::TO_MONEY_INSERT_INESERTED) {
	_message = "Введені купюри успішно вставлені";
    _actionsLabels = QList<QString>() << "Ок";
}
TOMoneyInsertInsertedAction::~TOMoneyInsertInsertedAction() {}
void TOMoneyInsertInsertedAction::beforeAction() {
    _uc->printMessage(_message, _actionsLabels);
}
void TOMoneyInsertInsertedAction::afterAction() {}
void TOMoneyInsertInsertedAction::setupForUI(UIController *uc, SessionController *sc) {
    Action::setupUI(uc, sc);
    beforeAction();
}
void TOMoneyInsertInsertedAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new TOMainMenuAction());
}


TOWorkFinishedAction::TOWorkFinishedAction(): Action(ActionType::TO_WORK_FINISHED) {
	_message = "Закінчуємо роботу в режимі технічного спеціаліста. Банкомат переходить в звичайний режим";
    _actionsLabels = QList<QString>() << "Ок";
}
TOWorkFinishedAction::~TOWorkFinishedAction() {}
void TOWorkFinishedAction::beforeAction() {
    _uc->printMessage(_message, _actionsLabels);
}
void TOWorkFinishedAction::afterAction() {}
void TOWorkFinishedAction::setupForUI(UIController *uc, SessionController *sc) {
    Action::setupUI(uc, sc);
    beforeAction();
}
void TOWorkFinishedAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->reset(false);
}

