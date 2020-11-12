#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QDateTime>
#include <QString>

class Account
{
    QString _cardNumber;
    QDateTime _expirationDate;
    QString _pin;
    bool _blocked;
    double _balance;
public:
    Account(QString card, QDateTime date, QString pin);
    Account(QString card, QDateTime date, QString pin, const bool blocked, const double balance);
    bool blocked() const;
    void setBlocked(bool blocked);
    QString pin() const;
    void setPin(const QString &pin);
    QDateTime expirationDate() const;
    void setExpirationDate(const QDateTime &expirationDate);
    QString cardNumber() const;
    void setCardNumber(const QString &cardNumber);
    double balance() const;
    void setBalance(const double val);
};

#endif // ACCOUNT_H
