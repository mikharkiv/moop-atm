#ifndef CARDWINDOW_H
#define CARDWINDOW_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class CardWindow;
}

class CardWindow : public QDialog
{
	Q_OBJECT

public:
	explicit CardWindow(QWidget *parent = nullptr);
	~CardWindow();

	void setKnownCards(QList<QString> &cards);
	void setMinCardNumLength(int minLen);
	void setMaxCardNumLength(int maxLen);

signals:
	void onWindowClosed();
	void onCardChosen(QString cardNum);

private slots:
	void on_okButton_clicked();
	void on_cancelButton_clicked();
	void on_cardNumEdit_textChanged(const QString &arg1);
	void onKnownCardButtonClicked(int id);

private:
	Ui::CardWindow *ui;

	QButtonGroup cardsButtons;
	QList<QString> knownCards;
	int minCardNumLength;
	int maxCardNumLength;

	void checkCardNumber();
};

#endif // CARDWINDOW_H
