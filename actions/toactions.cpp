#include "toactions.h"
#include "controllers/sessioncontroller.h"
#include "controllers/uicontroller.h"


TOMenuAction::TOMenuAction(): Action(ActionType::TO_MENU) {_isPinRestricted = true;}
void TOMenuAction::beforeAction() {
	_sc->setupForAction(new TOMainMenuAction());
}
void TOMenuAction::actionPerformed(UIActionType actionType, const QString &param) {}

TOMainMenuAction::TOMainMenuAction(): Action(ActionType::TO_MAIN_MENU) {
    _message = "Меню технічого спеціаліста.\nВиберіть операцію:";
	_actionsLabels = QList<QString>() << "Створити нову картку" << "Заблокувати картку" << "Розблокувати картку" << "Поповнити сховище купюр" << "Вийти з режиму ТО";
	_canCancel = true;
}
void TOMainMenuAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED) {
		int action = param.toInt();
		switch (action) {
			case 0: _sc->setupForAction(new TONewCardMenuAction()); break;
			case 1: _sc->setupForAction(new TOCardBlockMenuAction()); break;
			case 2: _sc->setupForAction(new TOCardUnblockMenuAction()); break;
			case 3: _sc->setupForAction(new TOMoneyInsertMenuAction()); break;
			case 4: _sc->setupForAction(new TOWorkFinishedAction()); break;
		}
	} else if (actionType == UIActionType::CANCELED)
		_sc->setupForAction(new TOWorkFinishedAction());
}

TONewCardMenuAction::TONewCardMenuAction(): Action(ActionType::TO_NEW_CARD_MENU) {
    _message = "Введіть номер картки:";
	_canType = true;
	_canCancel = true;
}

void TONewCardMenuAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::INPUT) {
		if (_sc->checkCardExists(param)) {
			_sc->setupForAction(new TONewCardExistsAction());
		} else {
			_sc->placeToMemory(param);
			_sc->setupForAction(new TONewCardCreatedAction());
		}
	} else if (actionType == UIActionType::CANCELED)
		_sc->setupForAction(new TOMainMenuAction());
}

TONewCardExistsAction::TONewCardExistsAction(): Action(ActionType::TO_NEW_CARD_EXISTS) {
	_message = "Картка вже існує. Спробуйте іншу";
    _actionsLabels = QList<QString>() << "Ок";
}
void TONewCardExistsAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new TOMainMenuAction());
}

TONewCardCreatedAction::TONewCardCreatedAction(): Action(ActionType::TO_NEW_CARD_CREATED) {
	_message = "Картку успішно створено. ПІН надруковано на чеку";
    _actionsLabels = QList<QString>() << "Ок";
}
void TONewCardCreatedAction::beforeAction() {
	_sc->showReceipt(QString("Створено нову картку\nПІН: %1").arg(_sc->createCard(_sc->takeFromMemory())));
    _uc->printMessage(_message, _actionsLabels);
}
void TONewCardCreatedAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new TOMainMenuAction());
}

TOCardBlockMenuAction::TOCardBlockMenuAction(): Action(ActionType::TO_CARD_BLOCK_MENU) {
	_message = "Введіть номер картки для блокування";
	_canType = true;
	_canCancel = true;
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
	} else if (actionType == UIActionType::CANCELED)
		_sc->setupForAction(new TOMainMenuAction());
}

TOCardBlockNotExistsAction::TOCardBlockNotExistsAction(): Action(ActionType::TO_CARD_BLOCK_NOT_EXISTS) {
	_message = "Картки не існує. Спробуйте іншу";
    _actionsLabels = QList<QString>() << "Ок";
}
void TOCardBlockNotExistsAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new TOMainMenuAction());
}

TOCardBlockAlreadyBlockedAction::TOCardBlockAlreadyBlockedAction(): Action(ActionType::TO_CARD_BLOCK_ALREADY_BLOCKED) {
	_message = "Картка вже заблокована";
    _actionsLabels = QList<QString>() << "Ок";
}
void TOCardBlockAlreadyBlockedAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new TOMainMenuAction());
}

TOCardBlockBlockedAction::TOCardBlockBlockedAction(): Action(ActionType::TO_CARD_BLOCK_BLOCKED) {
	_message = "Введену картку успішно заблоковано";
    _actionsLabels = QList<QString>() << "Ок";
}
void TOCardBlockBlockedAction::beforeAction() {
    _uc->printMessage(_message, _actionsLabels);
	QString c = _sc->takeFromMemory();
	_sc->blockCard(c);
	_sc->showReceipt(QString("Заблоковано картку: %1").arg(c));
}
void TOCardBlockBlockedAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new TOMainMenuAction());
}

TOCardBlockExpiredAction::TOCardBlockExpiredAction(): Action(ActionType::TO_CARD_BLOCK_EXPIRED) {
	_message = "Термін дії введеної картки сплив. Спробуйте іншу";
    _actionsLabels = QList<QString>() << "Ок";
}
void TOCardBlockExpiredAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new TOMainMenuAction());
}

TOCardUnblockMenuAction::TOCardUnblockMenuAction(): Action(ActionType::TO_CARD_UNBLOCK_MENU) {
	_message = "Введіть номер картки для розблокування";
	_canType = true;
	_canCancel = true;
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
	} else if (actionType == UIActionType::CANCELED)
		_sc->setupForAction(new TOMainMenuAction());
}

TOCardUnblockNotBlockedAction::TOCardUnblockNotBlockedAction(): Action(ActionType::TO_CARD_UNBLOCK_NOT_BLOCKED) {
	_message = "Введену картку не заблоковано. Спробуйте іншу";
    _actionsLabels = QList<QString>() << "Ок";
}
void TOCardUnblockNotBlockedAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED)	_sc->setupForAction(new TOMainMenuAction());
}

TOCardUnblockUnblockedAction::TOCardUnblockUnblockedAction(): Action(ActionType::TO_CARD_UNBLOCK_UNBLOCKED) {
	_message = "Введену картку успішно розблоковано";
    _actionsLabels = QList<QString>() << "Ок";
}
void TOCardUnblockUnblockedAction::beforeAction() {
    _uc->printMessage(_message, _actionsLabels);
	QString c = _sc->takeFromMemory();
	_sc->unblockCard(c);
	_sc->showReceipt(QString("Картку розблоковано: %1").arg(c));
}
void TOCardUnblockUnblockedAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED) _sc->setupForAction(new TOMainMenuAction());
}

TOMoneyInsertMenuAction::TOMoneyInsertMenuAction(): Action(ActionType::TO_MONEY_INSERT_MENU) {
	_message = "Вставте купюри в купюроприймач";
	_canInsertMoney = true;
	_canCancel = true;
}
void TOMoneyInsertMenuAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::MONEY_INSERTED) _sc->setupForAction(new TOMoneyInsertInsertedAction());
	else if (actionType == UIActionType::CANCELED) _sc->setupForAction(new TOMainMenuAction());
}

TOMoneyInsertInsertedAction::TOMoneyInsertInsertedAction(): Action(ActionType::TO_MONEY_INSERT_INESERTED) {
	_message = "Введені купюри успішно вставлені";
    _actionsLabels = QList<QString>() << "Ок";
}
void TOMoneyInsertInsertedAction::beforeAction() {
	_uc->printMessage(_message, _actionsLabels);
	_sc->showReceipt(QString("Сховище купюр успішно поповнено купюрами"));
}
void TOMoneyInsertInsertedAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED) _sc->setupForAction(new TOMainMenuAction());
}

TOWorkFinishedAction::TOWorkFinishedAction(): Action(ActionType::TO_WORK_FINISHED) {
	_message = "Закінчуємо роботу в режимі технічного спеціаліста. Банкомат переходить в звичайний режим";
    _actionsLabels = QList<QString>() << "Ок";
}
void TOWorkFinishedAction::actionPerformed(UIActionType actionType, const QString &param) {
    if (actionType == UIActionType::ACTION_CLICKED)
		_sc->reset(false);
}
