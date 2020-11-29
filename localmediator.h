#ifndef LOCALMEDIATOR_H
#define LOCALMEDIATOR_H


#include "bank.h"
#include "imediator.h"

class LocalMediator : public IMediator
{
Bank& _bank;
BankResponse<Account> doGetAccount(QString id);
BankResponse<ResponseStatus> doCreateAccount(const Account &acc);
BankResponse<double> doWithdraw(QString id, const double amount);
BankResponse<double> doTop_up(QString id, const double amount);
BankResponse<ResponseStatus> doBlock(QString id);
BankResponse<ResponseStatus> doUnblock(QString id);
BankResponse<bool> doCheckPin(QString id, QString pin);
BankResponse<ResponseStatus> doSetPin(QString id, QString newPin);
public:
    LocalMediator(Bank& bank);

    // IMediator interface
};

#endif // LOCALMEDIATOR_H
