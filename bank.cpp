#include "bank.h"

Bank::Bank() : _db(DBController())
{

}

BankResponse<Account> Bank::getAccount(QString id)
{
    Account acc = _db.getAccount(id);
    return BankResponse<Account>(acc);
}

BankResponse<ResponseStatus> Bank::createAccount(const Account &acc)
{
    return _db.addAccount(acc) ? BankResponse<ResponseStatus>(ResponseStatus::OK) : BankResponse<ResponseStatus>(ResponseStatus::ERROR);
}

BankResponse<double> Bank::withdraw(QString id, const double amount)
{
    Account acc = _db.getAccount(id);
    double bal = acc.balance();
    if (bal < amount)
        return BankResponse<double>(NOT_ENOUGH);
    acc.setBalance(bal - amount);
    _db.updateAccount(acc);
    return BankResponse<double>(acc.balance());
}

BankResponse<double> Bank::top_up(QString id, const double amount)
{
    Account acc = _db.getAccount(id);
    double bal = acc.balance();
    acc.setBalance(bal + amount);
    _db.updateAccount(acc);
    return BankResponse<double>(acc.balance());
}

BankResponse<ResponseStatus> Bank::block(QString id)
{
    Account acc = _db.getAccount(id);
    acc.setBlocked(true);
    _db.updateAccount(acc);
    return BankResponse<ResponseStatus>(OK);
}

BankResponse<ResponseStatus> Bank::unblock(QString id)
{
    Account acc = _db.getAccount(id);
    acc.setBlocked(false);
    _db.updateAccount(acc);
    return BankResponse<ResponseStatus>(OK);
}

BankResponse<bool> Bank::checkPin(QString id, QString pin)
{
    Account acc = _db.getAccount(id);
    return BankResponse<bool>(acc.pin() == pin);
}

BankResponse<ResponseStatus> Bank::setPin(QString id, QString newPin)
{
    Account acc = _db.getAccount(id);
    acc.setPin(newPin);
    _db.updateAccount(acc);
    return BankResponse<ResponseStatus>(OK);
}
