#ifndef ATMMAINWINDOW_H
#define ATMMAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class ATMMainWindow; }
QT_END_NAMESPACE

class ATMMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ATMMainWindow(QWidget *parent = nullptr);
    ~ATMMainWindow();

	void setCanCardInsert(bool value);
	void setCanCardEject(bool value);
	void setCanTOMode(bool value);
	void setCanMoneyInsert(bool value);
	void setCanType(bool value);
	void setCanCancel(bool value);
	void resetInput();

	void setDisplayText(const QString &message, const QList<QString> &actionsTexts, const QString &typingHint, const QString& currentInput);

signals:
	void onCardInsertClicled();
	void onCardEjectClicled();
	void onMoneyInsertClicled();
	void onTOModeClicled();

	void onActionButtonClicled(int id);

	void onInputEntered();
	void onCancelClicled();

private slots:
	void on_insertCardButton_clicked();
	void on_insertMoneyButton_clicked();
	void on_ejectCardButton_clicked();
	void on_techModeButton_clicked();

	void onKeybButtonClicked(int id);
	void onActionButtonClicked(int id);
	
private:
    Ui::ATMMainWindow *ui;

	int maxInputLen = 20;

	QButtonGroup actionsButtons;
	QButtonGroup keyboardButtons;

	QString currentInput;
	
	QString currentMessage;
	QList<QString> currentActionsLabels;
	QString currentTypeHint;

	bool canCardInsert;
	bool canCardEject;
	bool canTOMode;
	bool canMoneyInsert;
	bool canType;
	bool canCancel;
};
#endif // ATMMAINWINDOW_H
