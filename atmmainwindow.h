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
	void setCanTOMode(bool value);
	void setCanMoneyInsert(bool value);
	void setCanType(bool value, bool hidden = false);
	void setCanCancel(bool value);
	void resetInput();

	void print(const QString& message, const QList<QString>& actions = QList<QString>(), const QString typingHint = "");

signals:
	void onCardInsertClicked();
	void onMoneyInsertClicked();
	void onTOModeClicked();

	void onActionButtonClicked(int id);

	void onInputEntered(QString& input);
	void onCancelClicked();

private slots:
	void on_insertCardButton_clicked();
	void on_insertMoneyButton_clicked();
	void on_techModeButton_clicked();

	void onKeybButtonClicked(int id);
	void onActionButClicked(int id);
	
	void on_cancelKeybButton_clicked();

	void on_enterKeybButton_clicked();

	void on_backspKeybButton_clicked();

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
	bool canTOMode;
	bool canMoneyInsert;
	bool canType;
	bool canCancel;
	bool isTypingHidden;

	void setDisplayText(const QString &message, const QList<QString> &actionsTexts, const QString &typingHint, const QString& currentInput);
};
#endif // ATMMAINWINDOW_H
