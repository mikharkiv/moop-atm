#include "actions.h"
#include "controllers/sessioncontroller.h"
#include "controllers/uicontroller.h"

MainMenuAction::MainMenuAction(): Action(ActionType::MAIN_MENU) {
	_canInsertCard = true;
	_canEnterTO = true;
	_message = "Банкомат вітає вас. Вставте картку для виконання операцій";
}
MainMenuAction::~MainMenuAction() {}
void MainMenuAction::beforeAction() {
	_uc->printMessage(_message);
}
void MainMenuAction::afterAction() {}
void MainMenuAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void MainMenuAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::CARD_INSERTED) {
		// maybe TODO checking
		_sc->setupForAction(new CardInsertAction());
	}
}

CardInsertAction::CardInsertAction(): Action(ActionType::CARD_INSERT_MENU) {
	_isPinRestricted = true;
}
CardInsertAction::~CardInsertAction() {}
void CardInsertAction::beforeAction() {
	if (_sc->checkCardExpired(_sc->getCurrentCard()))
		_sc->setupForAction(new CardExpiredAction());
	else if (_sc->checkCardBlocked(_sc->getCurrentCard()))
		_sc->setupForAction(new CardBlockedAction());
	else
		_sc->setupForAction(new UserMenuAction());
}
void CardInsertAction::afterAction() {}
void CardInsertAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void CardInsertAction::actionPerformed(UIActionType actionType, const QString &param) {}

CardBlockedAction::CardBlockedAction(): Action(ActionType::CARD_INSERT_BLOCKED) {
	_message = "Картка заблокована і не може бути використана для здійснення операцій. \nЗверніться до співробітника банку для перевипуску картки";
	_actionsLabels = QList<QString>() << "Ок";
}
CardBlockedAction::~CardBlockedAction() {}
void CardBlockedAction::beforeAction() {
	_uc->printMessage(_message, _actionsLabels);
}
void CardBlockedAction::afterAction() {}
void CardBlockedAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void CardBlockedAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new MainMenuAction());
}

CardExpiredAction::CardExpiredAction(): Action(ActionType::CARD_INSERT_OUTDATED) {
	_message = "Термін дії картки вийшов. \nКартка не може бути використана для здійснення операцій. \nЗверніться до співробітника банку для перевипуску картки";
	_actionsLabels = QList<QString>() << "Ок";
}
CardExpiredAction::~CardExpiredAction() {}
void CardExpiredAction::beforeAction() {
	_uc->printMessage(_message, _actionsLabels);
}
void CardExpiredAction::afterAction() {}
void CardExpiredAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void CardExpiredAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new MainMenuAction());
}

UserMenuAction::UserMenuAction(): Action(ActionType::USER_MENU) {
	_message = "Меню користувача\nВиберіть потрібну дію:";
	_actionsLabels = QList<QString>() << "Видача готівки" << "Поповнення балансу" << "Переказ коштів" << "Дізнатись баланс"
 << "Зміна ПІН" << "Завершити роботу";
}
UserMenuAction::~UserMenuAction() {}
void UserMenuAction::beforeAction() {
	_uc->printMessage(_message, _actionsLabels);
}
void UserMenuAction::afterAction() {}
void UserMenuAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void UserMenuAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED) {
		int code = param.toInt();
		switch (code) {
			case 0: _sc->setupForAction(new GetCashAction()); break;
			case 1: _sc->setupForAction(new TopUpBalanceAction()); break;
			case 2: _sc->setupForAction(new MoneyTransferFirstAction()); break;
			case 3: _sc->setupForAction(new BalancePrintedAction()); break;
			case 4: _sc->setupForAction(new PinChangedAction()); break;
			case 5: _sc->setupForAction(new WorkFinishedAction()); break;
		}
	}
}

GetCashAction::GetCashAction(): Action(ActionType::CASH_WITHDRAWAL_MENU) {
	_message = "Введіть необхідну суму для видачі:";
	_canType = true;
	_canCancel = true;
}
GetCashAction::~GetCashAction() {}
void GetCashAction::beforeAction() {
	_uc->printMessage(_message);
}
void GetCashAction::afterAction() {}
void GetCashAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void GetCashAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::INPUT) {
		if (!_sc->canGiveSum(param.toInt())) {
			_sc->setupForAction(new NoBanknotesAction());
		} else if (!_sc->hasEnoughMoney(param.toInt())) {
			_sc->setupForAction(new NoBalanceAction());
		} else {
			_sc->giveCash(param.toInt());
			_sc->placeToMemory(param);
			_sc->setupForAction(new CashGivenAction());
		}
	} else if (actionType == UIActionType::CANCELED) {
		_sc->setupForAction(new UserMenuAction());
	}
}

NoBanknotesAction::NoBanknotesAction(): Action(ActionType::CASH_WITHDRAWAL_NO_CASH) {
	_message = "В банкоматі бракує купюр. Спробуйте іншу суму";
	_actionsLabels = QList<QString>() << "Ок";
}
NoBanknotesAction::~NoBanknotesAction() {}
void NoBanknotesAction::beforeAction() {
	_uc->printMessage(_message, _actionsLabels);
}
void NoBanknotesAction::afterAction() {}
void NoBanknotesAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void NoBanknotesAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new UserMenuAction());
}

NoBalanceAction::NoBalanceAction(): Action(ActionType::CASH_WITHDRAWAL_NO_BALANCE) {
	_message = "Бракує коштів на балансі. Спробуйте іншу суму";
	_actionsLabels = QList<QString>() << "Ок";
}
NoBalanceAction::~NoBalanceAction() {}
void NoBalanceAction::beforeAction() {
	_uc->printMessage(_message, _actionsLabels);
	_uc->showReceipt("Спроба зняти кошти з картки. Помилка: бракує коштів");
}
void NoBalanceAction::afterAction() {}
void NoBalanceAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void NoBalanceAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new UserMenuAction());
}

CashGivenAction::CashGivenAction(): Action(ActionType::CASH_WITHDRAWAL_WITHDRAWED) {
	_message = "Готівку видано. Не забудьте забрати чек і завершити роботу з банкоматом";
	_actionsLabels = QList<QString>() << "Ок";
}
CashGivenAction::~CashGivenAction() {}
void CashGivenAction::beforeAction() {
	_uc->printMessage(_message, _actionsLabels);
	_uc->showReceipt(QString("З картки було знято %1 грн").arg(_sc->takeFromMemory()));
}
void CashGivenAction::afterAction() {}
void CashGivenAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void CashGivenAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new UserMenuAction());
}

TopUpBalanceAction::TopUpBalanceAction(): Action(ActionType::CASH_ADD_MENU) {
	_message = "Внесіть необхідну суму коштів";
	_canInsertMoney = true;
	_canCancel = true;
}
TopUpBalanceAction::~TopUpBalanceAction() {}
void TopUpBalanceAction::beforeAction() {
	_uc->printMessage(_message);
}
void TopUpBalanceAction::afterAction() {}
void TopUpBalanceAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void TopUpBalanceAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::MONEY_INSERTED) {
		_sc->addBalance(param.toInt());
		_sc->placeToMemory(param);
		_sc->setupForAction(new BalanceToppedUpAction());
	} else if (actionType == UIActionType::CANCELED) {
		_sc->setupForAction(new UserMenuAction());
	}
}

BalanceToppedUpAction::BalanceToppedUpAction(): Action(ActionType::CASH_ADD_ADDED) {
	_message = "Баланс поповнено на %1 грн";
	_actionsLabels = QList<QString>() << "Ок";
}
BalanceToppedUpAction::~BalanceToppedUpAction() {}
void BalanceToppedUpAction::beforeAction() {
	_uc->printMessage(_message.arg(_sc->takeFromMemory()), _actionsLabels);
}
void BalanceToppedUpAction::afterAction() {}
void BalanceToppedUpAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void BalanceToppedUpAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new UserMenuAction());
}

MoneyTransferFirstAction::MoneyTransferFirstAction(): Action(ActionType::MONEY_TRANSFER_MENU1) {
	_message = "Введіть необхідну суму";
	_canType = true;
}
MoneyTransferFirstAction::~MoneyTransferFirstAction() {}
void MoneyTransferFirstAction::beforeAction() {
	_uc->printMessage(_message);
}
void MoneyTransferFirstAction::afterAction() {}
void MoneyTransferFirstAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void MoneyTransferFirstAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::INPUT) {
		if (!_sc->hasEnoughMoney(param.toInt())) {
		   _sc->setupForAction(new NoBalanceAction());
		} else {
			_sc->placeToMemory(param);
			_sc->setupForAction(new MoneyTransferSecondAction());
		}
	}  else if (actionType == UIActionType::CANCELED) {
		_sc->setupForAction(new UserMenuAction());
	}
}

MoneyTransferSecondAction::MoneyTransferSecondAction(): Action(ActionType::MONEY_TRANSFER_MENU2) {
	_message = "Введіть номер картки";
}
MoneyTransferSecondAction::~MoneyTransferSecondAction() {}
void MoneyTransferSecondAction::beforeAction() {
	_uc->printMessage(_message);
}
void MoneyTransferSecondAction::afterAction() {}
void MoneyTransferSecondAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void MoneyTransferSecondAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::INPUT) {
		if (_sc->checkCardBlocked(param) || !_sc->checkCardExists(param) || _sc->checkCardExpired(param)) {
			_sc->takeFromMemory();
			_sc->setupForAction(new WrongCardAction());
		} else {
			QString money = _sc->takeFromMemory();
			_sc->transferMoney(money.toInt(), param);
			_sc->setupForAction(new MoneyTransferSecondAction());
		}
	}  else if (actionType == UIActionType::CANCELED) {
		_sc->setupForAction(new UserMenuAction());
	}
}

WrongCardAction::WrongCardAction(): Action(ActionType::MONEY_TRANSFER_WRONG_CARD) {
	_message = "Неправильний номер картки або картка недійсна. Спробуйте ще раз";
	_actionsLabels = QList<QString>() << "Ок";
}
WrongCardAction::~WrongCardAction() {}
void WrongCardAction::beforeAction() {
	_uc->printMessage(_message, _actionsLabels);
}
void WrongCardAction::afterAction() {}
void WrongCardAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void WrongCardAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new UserMenuAction());
}

MoneyTransferedAction::MoneyTransferedAction(): Action(ActionType::MONEY_TRANSFER_TRANSFERED) {
	_message = "Гроші успішно переказано";
	_actionsLabels = QList<QString>() << "Ок";
}
MoneyTransferedAction::~MoneyTransferedAction() {}
void MoneyTransferedAction::beforeAction() {
	_uc->printMessage(_message, _actionsLabels);
}
void MoneyTransferedAction::afterAction() {}
void MoneyTransferedAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void MoneyTransferedAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new UserMenuAction());
}

BalancePrintedAction::BalancePrintedAction(): Action(ActionType::GET_BALANCE_PRINTED) {
	_message = "Баланс надруковано на чеку. Не забудьте завершити роботу з банкоматом і знищити чек";
	_actionsLabels = QList<QString>() << "Ок";
}
BalancePrintedAction::~BalancePrintedAction() {}
void BalancePrintedAction::beforeAction() {
	_uc->printMessage(_message, _actionsLabels);
	_uc->showReceipt(QString("Баланс по картці: %1").arg(QString::number(_sc->getBalance())));
}
void BalancePrintedAction::afterAction() {}
void BalancePrintedAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void BalancePrintedAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new UserMenuAction());
}

PinChangedAction::PinChangedAction(): Action(ActionType::PIN_CHANGE_PRINTED) {
	_message = "Новий ПІН надруковано на чеку. Нікому його не показуйте і знищте одразу після того, як запам'ятаєте ПІН";
	_actionsLabels = QList<QString>() << "Ок";
}
PinChangedAction::~PinChangedAction() {}
void PinChangedAction::beforeAction() {
	_uc->printMessage(_message, _actionsLabels);
	_uc->showReceipt(QString("НІКОМУ НЕ ПОКАЗУЙТЕ ЦЕЙ ЧЕК\nОДРАЗУ ЗНИЩТЕ ЙОГО\n\nВаш новий ПІН:\n%1").arg(_sc->changePIN()));
}
void PinChangedAction::afterAction() {}
void PinChangedAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void PinChangedAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED)
		_sc->setupForAction(new UserMenuAction());
}

WorkFinishedAction::WorkFinishedAction(): Action(ActionType::PIN_CHANGE_PRINTED) {
	_message = "Роботу з банкоматом завершено. Не забудьте забрати свою картку";
	_actionsLabels = QList<QString>() << "Ок";
}
WorkFinishedAction::~WorkFinishedAction() {}
void WorkFinishedAction::beforeAction() {
	_uc->printMessage(_message, _actionsLabels);
}
void WorkFinishedAction::afterAction() {}
void WorkFinishedAction::setupForUI(UIController *uc, SessionController *sc) {
	Action::setupUI(uc, sc);
	beforeAction();
}
void WorkFinishedAction::actionPerformed(UIActionType actionType, const QString &param) {
	if (actionType == UIActionType::ACTION_CLICKED)
		_sc->reset(false);
}

//
//MainMenuAction::MainMenuAction(): Action(ActionType::) {}
//MainMenuAction::~MainMenuAction() {}
//void MainMenuAction::beforeAction() {
//
//}
//void MainMenuAction::afterAction() {
//
//}
//void MainMenuAction::setupForUI(UIController *uc, SessionController *sc) {
//	Action::setupUI(uc, sc);
//
//}
//void MainMenuAction::actionPerformed(UIActionType actionType, const QString &param) {
//
//}

