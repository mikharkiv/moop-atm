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

	void setDisplayText(const QString &message, const QList<QString> &actionsTexts, const QString &typingHint);

private slots:
	void on_insertCardButton_clicked();

	void on_insertMoneyButton_clicked();

private:
    Ui::ATMMainWindow *ui;

	QButtonGroup actionsButtons;
	QButtonGroup keyboardButtons;

	QString currentInput;

	bool canCardInsert;
	bool canCardEject;
	bool canTOMode;
	bool canMoneyInsert;
	bool canType;
	bool canCancel;
};
#endif // ATMMAINWINDOW_H
