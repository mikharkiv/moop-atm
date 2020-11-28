#ifndef RECEIPTWINDOW_H
#define RECEIPTWINDOW_H

#include <QDialog>

namespace Ui {
class ReceiptWindow;
}

class ReceiptWindow : public QDialog
{
	Q_OBJECT

public:
	explicit ReceiptWindow(QWidget *parent = nullptr);

	void setReceiptText(const QString& receiptText);
	~ReceiptWindow();

signals:
	void onWindowClosed();

private slots:
	void on_okButton_clicked();

private:
	Ui::ReceiptWindow *ui;
};

#endif // RECEIPTWINDOW_H
