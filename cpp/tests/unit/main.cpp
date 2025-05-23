#include <gtest/gtest.h>
#include <model/TModel.hpp>
#include "Models.h"
#include <thread>
#include <chrono>

// -------- INIT BASE --------
TEST(TModelerTest, InitMultipleDatabases)
{
    EXPECT_NO_THROW({
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
    });
}

// -------- CRUD SIMPLE --------
TEST(ClientModelTest, BasicCreateUpdateDelete)
{
    Client::tms.clear();
    Client cl;
    cl.name = "Timeless";

    EXPECT_NO_THROW(cl.create());
    EXPECT_FALSE(Client::tms.all().empty());
    
    cl.name = "Updated";
    EXPECT_NO_THROW(cl.update());

    EXPECT_NO_THROW(cl.del());
}

// -------- JOIN ET ASSERTIONS --------
TEST(JoinTest, PopulateAndQuery)
{
    Client::tms.clear();
    Product::tms.clear();
    Cmd::tms.clear();

    Client cl1, cl2;
    cl1.name = "Alice";
    cl2.name = "Bob";

    cl1.save();
    cl2.save();

    Product pr1, pr2;
    pr1.name = "Book";
    pr2.name = "Pen";

    pr1.save();
    pr2.save();

    Cmd cm1, cm2;
    cm1.client = cl1;
    cm1.product = pr1;
    cm2.client = cl2;
    cm2.product = pr2;

    cm1.save();
    cm2.save();

    auto allClients = Client::tms.all();
    auto allProducts = Product::tms.all();
    auto allCmds = Cmd::tms.all();

    EXPECT_EQ(allClients.size(), 2);
    EXPECT_EQ(allProducts.size(), 2);
    EXPECT_EQ(allCmds.size(), 2);
}

// -------- CALLBACK TEST (SIMPLIFIÉ POUR TEST) --------
TEST(ClientModelTest, OnChangeCallbacks)
{
    Tms<Client> tms;
    bool createCalled = false;
    bool updateCalled = false;
    bool deleteCalled = false;

    tms.onCreate([&](auto) { createCalled = true; });
    tms.onUpdate([&](auto) { updateCalled = true; });
    tms.onDelete([&](auto) { deleteCalled = true; });

    Client cl;
    cl.name = "Tim";

    cl.create(); // devrait déclencher onCreate
    cl.name = "Tim Updated";
    cl.update(); // onUpdate
    cl.del(); // onDelete

    EXPECT_TRUE(createCalled);
    EXPECT_TRUE(updateCalled);
    EXPECT_TRUE(deleteCalled);
}

// -------- ENTRY POINT TEST --------
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}