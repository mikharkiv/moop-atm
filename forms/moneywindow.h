#ifndef MONEYWINDOW_H
#define MONEYWINDOW_H

#include <QDialog>

namespace Ui {
class MoneyWindow;
}

class MoneyWindow : public QDialog
{
	Q_OBJECT

public:
	explicit MoneyWindow(QWidget *parent = nullptr);
	~MoneyWindow();

private:
	Ui::MoneyWindow *ui;
};

#endif // MONEYWINDOW_H
