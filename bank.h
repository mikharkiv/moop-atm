#ifndef BANK_H
#define BANK_H

#include "account.h"
#include "dbcontroller.h"
#include <QString>

enum ResponseStatus {
    OK, NOT_FOUND, ERROR, NOT_ENOUGH
};

template<class Value>
struct BankResponse {
    const ResponseStatus status;
    const Value value;
    BankResponse(const Value& val) : status(ResponseStatus::OK), value(val) {}
    BankResponse(const ResponseStatus resp) : status(resp), value(Value()) {}
    BankResponse(Value&& val) : status(ResponseStatus::OK), value(val) {}
};

template <>
struct BankResponse<ResponseStatus> {
    const ResponseStatus status;
    BankResponse(const ResponseStatus s) : status(s){}
};

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
