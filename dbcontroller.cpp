#include "dbcontroller.h"

#include <QDateTime>

void DBController::initDb()
{

    QSqlQuery create_query;
    QString str = "CREATE TABLE IF NOT EXISTS Account ("
                "card_number text PRIMARY KEY NOT NULL, "
                "expiration integer NOT NULL, "
                "pin text NOT NULL, "
                "blocked integer NOT NULL, "
                "balance REAL DEFAULT 0"
                ");";
    bool b = create_query.exec(str);
    if (!b) {
        qDebug() << "Can not create a table";
    }
}

DBController::DBController(QString dbPath)
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(dbPath);
    _db.open();
    initDb();
}

DBController::~DBController()
{
    _db.close();
}

bool DBController::addAccount(const Account& acc)
{
    QSqlQuery addQuery;
    addQuery.prepare("INSERT INTO Account (card_number, expiration, pin, blocked) "
                     "VALUES (?, ?, ?, ?)");
    addQuery.bindValue(0, acc.cardNumber());
    addQuery.bindValue(1, acc.expirationDate().toSecsSinceEpoch());
    addQuery.bindValue(2, acc.pin());
    addQuery.bindValue(3, acc.blocked() ? 1 : 0);
    return addQuery.exec();
}

bool DBController::updateAccount(const Account& acc)
{
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE Account "
                     "SET "
                     "pin = ?, "
                     "blocked = ?, "
                     "balance = ? "
                     "WHERE card_number = ?"
                     );
    updateQuery.bindValue(0, acc.pin());
    updateQuery.bindValue(1, acc.blocked() ? 1 : 0);
    updateQuery.bindValue(2, acc.balance());
    updateQuery.bindValue(3, acc.cardNumber());
    return updateQuery.exec();
}

Account DBController::getAccount(const QString& num)
{
    QSqlQuery getQuery;
    getQuery.prepare("SELECT card_number, expiration, pin, blocked, balance FROM Account "
                     "WHERE card_number = ?");
    getQuery.bindValue(0, num);
    getQuery.exec();
    if (!getQuery.first())
        throw NotFoundException();
    QString card_num = getQuery.value(0).toString();
    QDateTime exp = QDateTime::fromSecsSinceEpoch(getQuery.value(1).toUInt());
    QString pin = getQuery.value(2).toString();
    bool blocked = getQuery.value(3).toBool();
    double balance = getQuery.value(4).toDouble();
    return Account(card_num, exp, pin, blocked, balance);
}
