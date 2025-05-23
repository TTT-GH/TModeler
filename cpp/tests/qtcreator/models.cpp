#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <thread>

#include <QTimer>
#include <QDebug>


#include "Models.h"


TM_MANAGER(Client)
TM_MANAGER(Product)
TM_MANAGER(Cmd)


void sleep(long dur){
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(5));
    }
}


void testInitTM()
{
    TModeler::start()
    .init(Tdb::Builder()
              .type(Tdb::Type::SQLITE)
              .dbDir("/tmp/sql")
              .dbName("test.db")
              .accept("models.shops")
              .accept("models.users")
              .get())
        .init(Tdb::Builder()
              .type(Tdb::Type::SQLITE)
              .host("localhost")
              .dbName("test2.db")
              .get());
}
