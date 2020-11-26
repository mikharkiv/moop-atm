#ifndef MONEYWINDOW_H
#define MONEYWINDOW_H

#include <QDialog>
#include <QMap>
#include <QButtonGroup>
#include <QLabel>

namespace Ui {
class MoneyWindow;
}

class MoneyWindow : public QDialog
{
	Q_OBJECT

public:
	explicit MoneyWindow(QWidget *parent = nullptr);
	~MoneyWindow();

private slots:
	void onInsertButtonClicked(int id);

	void on_cancelButton_clicked();

	void on_okButton_clicked();

private:
	Ui::MoneyWindow *ui;

	QMap<int, int> banknotes;
	QButtonGroup insertButtons;
	QList<QLabel*> insertedLabels;

	void checkBanknotesInserted();
};

#endif // MONEYWINDOW_H
