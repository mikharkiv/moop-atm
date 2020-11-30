#include "localmediator.h"

LocalMediator::LocalMediator(QSharedPointer<Bank> bank) : _bank(bank) {}

LocalMediator::~LocalMediator() {}

BankResponse<Account> LocalMediator::doGetAccount(QString id)
{
    return _bank->getAccount(id);
}

BankResponse<ResponseStatus> LocalMediator::doCreateAccount(const Account &acc)
{
    return _bank->createAccount(acc);
}

BankResponse<double> LocalMediator::doWithdraw(QString id, const double amount)
{
    return _bank->withdraw(id, amount);
}

BankResponse<double> LocalMediator::doTop_up(QString id, const double amount)
{
    return _bank->top_up(id, amount);
}

BankResponse<ResponseStatus> LocalMediator::doBlock(QString id)
{
    return _bank->block(id);
}

BankResponse<ResponseStatus> LocalMediator::doUnblock(QString id)
{
    return _bank->unblock(id);
}

BankResponse<bool> LocalMediator::doCheckPin(QString id, QString pin)
{
    return _bank->checkPin(id, pin);
}

BankResponse<ResponseStatus> LocalMediator::doSetPin(QString id, QString newPin)
{
    return _bank->setPin(id, newPin);
}
