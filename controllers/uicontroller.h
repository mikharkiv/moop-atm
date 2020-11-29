#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <QMainWindow>
#include <QDialog>
#include "atmmainwindow.h"
#include "forms/cardwindow.h"
#include "forms/moneywindow.h"
#include "forms/receiptwindow.h"

class UIController: public QObject
{
	Q_OBJECT

public:
	UIController(ATMMainWindow* mainWindow);
	~UIController();

	void setKnownCards(QList<QString>& cards);

	void showReceipt(const QString& message);
	void printMessage(const QString& message, const QList<QString>& actions = QList<QString>(), const QString& typingHint = "");

	void setMoneyInsertionEnabled(bool enabled);
	void setTypingEnabled(bool enabled, bool hidden = false);
	void setCancelingEnabled(bool enabled);
	void setTOModeEnabled(bool enabled);
	void setCardInsertionEnabled(bool enabled);

signals:
	void onTOModeClicked();
	void onCancelClicked();
	void onActionClicked(int id);
	void onInput(QString& input);
	void onMoneyInserted(QMap<int, int>& money);
	void onCardChosen(QString& card);

private slots:
	void onMainWinMoneyInsertClicked();
	void onMainWinCardInsertClicked();
	void onMainWinTOModeClicked();
	void onMainWinCancelClicked();
	void onMainWinActionButClicked(int id);
	void onMainWinInputEntered(QString& input);

	void onCWinCardChosen(QString cardNum);
	void onCWinClosed();

	void onMoneyWinMoneyInserted(QMap<int,int>& money);
	void onMoneyWinClosed();

private:
	ATMMainWindow* _mainWindow;
	ReceiptWindow* _receiptWindow;
	MoneyWindow* _moneyWindow;
	CardWindow* _cardWindow;
	QList<QString> _knownCards;

	void connectMainWindow();
	void connectMoneyWindow();
	void connectCardWindow();

	void showMoneyWindow();
	void showCardWindow(QList<QString>& knownCards);
};

#endif // UICONTROLLER_H
