#ifndef TSQLITE_H
#define TSQLITE_H

#include <string>
#include "Tdb.h"

struct sqlite3;

class TsqliteDriver : public TdbDriver {
private:
    sqlite3* db;
    int lastId;

public:
    TsqliteDriver();
    virtual ~TsqliteDriver();

    bool open(const std::string& dbName) override;
    void close() override;
    bool createTable(const std::string& tableScript) override;
    bool dropTable(const std::string& tableName) override;
    bool tableExists(const std::string& tableName) override;
    bool executeSQL(const std::string& sql) override;
    int64_t last_insert_rowid() override;
    std::string executeQuery(const std::string& query) override;
    bool deleteDatabase(const std::string& dbName) override;
};

#endif // TSQLITE_H
