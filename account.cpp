#include "account.h"

QString Account::pin() const
{
    return _pin;
}

void Account::setPin(const QString &pin)
{
    _pin = pin;
}

QDateTime Account::expirationDate() const
{
    return _expirationDate;
}

void Account::setExpirationDate(const QDateTime &expirationDate)
{
    _expirationDate = expirationDate;
}

QString Account::cardNumber() const
{
    return _cardNumber;
}

void Account::setCardNumber(const QString &cardNumber)
{
    _cardNumber = cardNumber;
}

double Account::balance() const
{
    return _balance;
}

void Account::setBalance(const double val)
{
    _balance = val;
}

Account::Account(QString card, QDateTime date, QString pin) : _cardNumber(card), _expirationDate(date), _pin(pin)
{

}

Account::Account(QString card, QDateTime date, QString pin, const bool blocked, const double balance)
    : _cardNumber(card), _expirationDate(date), _pin(pin), _blocked(blocked), _balance(balance)
{

}

bool Account::blocked() const
{
    return _blocked;
}

void Account::setBlocked(bool blocked)
{
    _blocked = blocked;
}
