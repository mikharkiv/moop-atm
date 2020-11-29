#ifndef BANK_H
#define BANK_H

#include "account.h"
#include "bankresponse.h"
#include "dbcontroller.h"
#include <QString>

class Bank
{
    DBController _db;
public:
    Bank();

    BankResponse<Account> getAccount(QString id);
    BankResponse<ResponseStatus> createAccount(const Account& acc);
    BankResponse<double> withdraw(QString id, const double amount);
    BankResponse<double> top_up(QString id, const double amount);
    BankResponse<ResponseStatus> block(QString id);
    BankResponse<ResponseStatus> unblock(QString id);
    BankResponse<bool> checkPin(QString id, QString pin);
    BankResponse<ResponseStatus> setPin(QString id, QString newPin);
};


#endif // BANK_H
