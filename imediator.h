#include "account.h"
#include "bankresponse.h"
#include <QString>

#ifndef IMEDIATOR_H
#define IMEDIATOR_H

class IMediator {
private:
    virtual BankResponse<Account> doGetAccount(QString id) = 0;
    virtual BankResponse<ResponseStatus> doCreateAccount(const Account& acc) = 0;
    virtual BankResponse<double> doWithdraw(QString id, const double amount) = 0;
    virtual BankResponse<double> doTop_up(QString id, const double amount) = 0;
    virtual BankResponse<ResponseStatus> doBlock(QString id) = 0;
    virtual BankResponse<ResponseStatus> doUnblock(QString id) = 0;
    virtual BankResponse<bool> doCheckPin(QString id, QString pin) = 0;
    virtual BankResponse<ResponseStatus> doSetPin(QString id, QString newPin) = 0;
public:
    BankResponse<Account> getAccount(QString id){ return doGetAccount(id); }
    BankResponse<ResponseStatus> createAccount(const Account& acc){ return doCreateAccount(acc); }
    BankResponse<double> withdraw(QString id, const double amount) {return doWithdraw(id, amount); }
    BankResponse<double> top_up(QString id, const double amount){ return doTop_up(id, amount); }
    BankResponse<ResponseStatus> block(QString id){ return doBlock(id); }
    BankResponse<ResponseStatus> unblock(QString id){ return doUnblock(id); }
    BankResponse<bool> checkPin(QString id, QString pin){ return doCheckPin(id, pin); }
    BankResponse<ResponseStatus> setPin(QString id, QString newPin){ return doSetPin(id, newPin); }
};

#endif // IMEDIATOR_H
