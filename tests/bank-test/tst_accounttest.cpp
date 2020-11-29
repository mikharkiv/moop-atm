#include <QtTest>
#include "bankresponse.h"
#include "dbcontroller.h"
#include "account.h"
#include "bank.h"


// add necessary includes here

class AccountTest : public QObject
{
    Q_OBJECT
    Bank *_bank;
public:
    AccountTest();
    ~AccountTest();

private slots:
    void cleanupTestCase();
    void create_account();
    void get_account();
    void balance();
    void pin();
    void block();
};

AccountTest::AccountTest()
{
    _bank = new Bank("test_db.sql");
}

AccountTest::~AccountTest()
{
}

void AccountTest::cleanupTestCase()
{
    delete _bank;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test_db.sql");
    db.open();
    QSqlQuery deleteDb("DROP TABLE Account");
    deleteDb.exec();
    db.close();
}

void AccountTest::create_account()
{
    auto create = _bank->createAccount(Account("1111", QDateTime::currentDateTime(), "1234"));
    QCOMPARE(create._status, OK);
    auto create2 = _bank->createAccount(Account("1111", QDateTime::currentDateTime(), "1234"));
    QCOMPARE(create2._status, ERROR);
}

void AccountTest::get_account()
{
    Account acc("1112", QDateTime::currentDateTime(), "4321");
    _bank->createAccount(acc);
    auto get1 = _bank->getAccount("1112");
    QCOMPARE(get1.status(), OK);

    auto accResp = get1.value();
    QCOMPARE(accResp.cardNumber(), acc.cardNumber());
    QCOMPARE(accResp.blocked(), acc.blocked());
    QCOMPARE(accResp.balance(), acc.balance());
    QCOMPARE(accResp.expirationDate().daysTo(acc.expirationDate()), 0);


    auto get2 = _bank->getAccount("abcd");
    QCOMPARE(get2.status(), NOT_FOUND);
}

void AccountTest::balance()
{
    Account acc("1113", QDateTime::currentDateTime(), "2345");
     _bank->createAccount(acc);

    auto balance1 = _bank->getAccount("1113");
    QCOMPARE(balance1.value().balance(), 0);

    auto top_up = _bank->top_up("1113", 67.35);
    QCOMPARE(top_up.value(), 67.35);

    auto withdraw = _bank->withdraw("1113", 50);
    QCOMPARE(withdraw.value(), 17.35);

    auto witdraw2 = _bank->withdraw("1113", 100);
    QCOMPARE(witdraw2.status(), NOT_ENOUGH);

    auto balance2 = _bank->getAccount("1113");
    QCOMPARE(balance2.value().balance(), 17.35);
}

void AccountTest::pin()
{
    Account acc("1114", QDateTime::currentDateTime(), "2345");
    _bank->createAccount(acc);

    auto pin = _bank->checkPin("1114", "2345");
    QCOMPARE(pin.value(), true);

    auto pin2 = _bank->checkPin("1114", "1245");
    QCOMPARE(pin2.value(), false);

    auto pin3 = _bank->setPin("1114", "7890");
    QCOMPARE(pin3._status, OK);

    auto pin4 = _bank->checkPin("1114", "7890");
    QCOMPARE(pin4.value(), true);

    auto pin5 = _bank->checkPin("1114", "2345");
    QCOMPARE(pin4.value(), true);
}

void AccountTest::block()
{
    Account acc("1115", QDateTime::currentDateTime(), "1256");
    _bank->createAccount(acc);

    auto acc1 = _bank->getAccount("1115");
    QCOMPARE(acc1.value().blocked(), false);

    auto acc2 = _bank->block("1115");
    QCOMPARE(acc2._status, OK);

    auto acc3 = _bank->getAccount("1115");
    QCOMPARE(acc3.value().blocked(), true);

    auto op1 = _bank->top_up("1115", 255);
    QCOMPARE(op1.status(), BLOCKED);

    auto op2 = _bank->withdraw("1115", 255);
    QCOMPARE(op2.status(), BLOCKED);

    auto op3 = _bank->setPin("1115", "2556");
    QCOMPARE(op3._status, BLOCKED);

    auto acc4 = _bank->unblock("1115");
    QCOMPARE(acc4._status, OK);

    auto acc5 = _bank->getAccount("1115");
    QCOMPARE(acc5.value().blocked(), false);
}

QTEST_APPLESS_MAIN(AccountTest)

#include "tst_accounttest.moc"
