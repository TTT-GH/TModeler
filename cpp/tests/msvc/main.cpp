#include <model/TModel.hpp>

#include "Models.h"

void testInitTM()
{
    TModeler::start()
        .init(Tdb::Builder()
            .type(Tdb::Type::SQLITE)
            .dbDir("/tmp/sql")
            .dbName("test.db")
            .get())
        .init(Tdb::Builder()
            .type(Tdb::Type::SQLITE)
            .host("localhost")
            .dbName("test2.db")
            .get());
}

Client client;
void comm()
{
    Tms<Client> tms;
    client.name = "Timeless";
    std::vector<Client> clients = { client };

    tms.name(); //remove generate pbs

    tms.onCreate([](auto keys)
        {
            Log::d("onCreate...");
        });
    tms.onUpdate([](auto keys)
        {
            Log::d("onUpdate...");
        });
    tms.onDelete([](auto keys)
        {
            Log::d("onDelete...");
        });
    tms.onModelChange([](auto keys)
        {
            Log::d("onModelChange...");
        });


    std::thread delayedThread([clients]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        client.create();

        std::thread delayedThread([clients]() {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            client._id = 10;
            client.create();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            client.name = "Template";
            client.update();
        });

        std::thread delayedThread2([clients]()
        {
                std::this_thread::sleep_for(std::chrono::seconds(2));
                client.save();
                std::this_thread::sleep_for(std::chrono::seconds(2));
                client.del();
        });


        while (true)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(5));
        }
    });
}


void joinTest()
{
    Client cl1, cl2, cl3;
    Product pr1, pr2, pr3;
    Cmd cm1, cm2, cm3, cm4, cm5, cm6;

    Client::tms.clear();
    Product::tms.clear();
    Cmd::tms.clear();
    Client::tms.name();
    Product::tms.name();
    Cmd::tms.name();

    if (Client::tms.all().empty())
    {
        cl1.name = "Olivier TAMBO";
        cl2.name = "Michel TAMBO";
        cl3.name = "Patie TAMBO";
        cl1.save();
        cl2.save();
        cl3.save();
    }
    if (Product::tms.all().empty())
    {
        pr1.name = "Poulet";
        pr2.name = "Poisson";
        pr3.name = "Porc";
        pr1.save();
        pr2.save();
        pr3.save();
    }
    if (Cmd::tms.all().empty())
    {
        cm1.client = cl1;
        cm1.product = pr1;
        cm1.save();
        cm2.client = cl1;
        cm2.product = pr2;
        cm2.save();
        cm3.client = cl2;
        cm3.product = pr3;
        cm3.save();
        cm4.client = cl2;
        cm4.product = pr1;
        cm4.save();
        cm5.client = cl1;
        cm5.product = pr2;
        cm5.save();
        cm6.client = cl2;
        cm6.product = pr3;
        cm6.save();
    }

    
    Log::d("Client: \n" + Client::tms.all().data());
    Log::d("Product: \n" + Product::tms.all().data());
    Log::d("Cmd: \n" + Cmd::tms.all().data());
}


int main(int argc, char** argv) {
    
    testInitTM();

    joinTest();

    return 0;
}
