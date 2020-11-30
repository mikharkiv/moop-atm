#include "bank.h"

Bank::Bank(QString dbPath) : _db(DBController(dbPath))
{

}

BankResponse<Account> Bank::getAccount(QString id)
{
    try {
        Account acc = _db.getAccount(id);
        return BankResponse<Account>(acc);
    }  catch (DBController::NotFoundException &e) {
        return BankResponse<Account>(NOT_FOUND);
    }
}

BankResponse<ResponseStatus> Bank::createAccount(const Account &acc)
{
    return _db.addAccount(acc) ? BankResponse<ResponseStatus>(ResponseStatus::OK) : BankResponse<ResponseStatus>(ResponseStatus::ERROR);
}

BankResponse<double> Bank::withdraw(QString id, const double amount)
{
    try {
        Account acc = _db.getAccount(id);
        double bal = acc.balance();
        if (QDateTime::currentDateTime().daysTo(acc.expirationDate()) <= 0)
            return BankResponse<double>(EXPIRED);
        if (acc.blocked())
            return BankResponse<double>(BLOCKED);
        if (bal < amount)
            return BankResponse<double>(NOT_ENOUGH);
        acc.setBalance(bal - amount);
        _db.updateAccount(acc);
        return BankResponse<double>(acc.balance());
    }   catch (DBController::NotFoundException &e) {
        return BankResponse<double>(NOT_FOUND);
    }

}

BankResponse<double> Bank::top_up(QString id, const double amount)
{
    try {
        Account acc = _db.getAccount(id);
        if (QDateTime::currentDateTime().daysTo(acc.expirationDate()) <= 0)
            return BankResponse<double>(EXPIRED);
        if (acc.blocked())
            return BankResponse<double>(BLOCKED);
        double bal = acc.balance();
        acc.setBalance(bal + amount);
        _db.updateAccount(acc);
        return BankResponse<double>(acc.balance());
    }  catch (DBController::NotFoundException &e) {
        return BankResponse<double>(NOT_FOUND);
    }
}

BankResponse<ResponseStatus> Bank::block(QString id)
{
    try {
        Account acc = _db.getAccount(id);
        acc.setBlocked(true);
        _db.updateAccount(acc);
        return BankResponse<ResponseStatus>(OK);
    }  catch (DBController::NotFoundException &e) {
        return BankResponse<ResponseStatus>(NOT_FOUND);
    }
}

BankResponse<ResponseStatus> Bank::unblock(QString id)
{
    try {
        Account acc = _db.getAccount(id);
        acc.setBlocked(false);
        _db.updateAccount(acc);
        return BankResponse<ResponseStatus>(OK);
    }  catch (DBController::NotFoundException &e) {
        return BankResponse<ResponseStatus>(NOT_FOUND);
    }
}

BankResponse<bool> Bank::checkPin(QString id, QString pin)
{
    try {
        Account acc = _db.getAccount(id);
        return BankResponse<bool>(acc.pin() == pin);
    }  catch (DBController::NotFoundException &e) {
        return BankResponse<bool>(NOT_FOUND);
    }
}

BankResponse<ResponseStatus> Bank::setPin(QString id, QString newPin)
{
    try {
        Account acc = _db.getAccount(id);
        if (acc.blocked())
            return BankResponse<ResponseStatus>(BLOCKED);
        acc.setPin(newPin);
        _db.updateAccount(acc);
        return BankResponse<ResponseStatus>(OK);
    } catch (DBController::NotFoundException &e) {
        return BankResponse<ResponseStatus>(NOT_FOUND);
    }
}
