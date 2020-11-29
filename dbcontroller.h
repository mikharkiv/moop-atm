#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H
#include "account.h"

#include <QtSql>

class DBController
{
    QSqlDatabase _db;
    void initDb();
public:
    DBController();
    ~DBController();
    bool addAccount(const Account& acc);
    bool updateAccount(const Account& acc);
    Account getAccount(const QString& num);
    class NotFoundException {};
};

#endif // DBCONTROLLER_H
