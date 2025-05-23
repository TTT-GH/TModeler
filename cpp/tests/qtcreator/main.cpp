#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <model/TModel.hpp>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QTimer>
#include <QDebug>

#include "Models.h"
#include "viewmodels.hpp"
#include "clientgenerator.h"

void comm()
{
    Tms<Client> tms;

    tms.onSave([](auto keys)
       {
           Log::d("onSave...\n" +
                  Client::tms.get(keys).data());
       });
    tms.onCreate([](auto keys)
     {
         Log::d("onCreate...\n" +
                Client::tms.get(keys).data());
     });
    tms.onUpdate([](auto keys)
     {
         Log::d("onUpdate...\n" +
                Client::tms.get(keys).data());
     });
    tms.onDelete([](auto keys)
     {
         Log::d("onDelete...\n" +
                vectorToString(keys));
     });
    tms.onModelChange([](auto keys)
      {
          Log::d("onModelChange...\n" +
                 vectorToString(keys));
      });
}

void bg(){
    // Dans ton code principal, par exemple dans main() ou ton contrôleur :
    QThread* thread = new QThread;
    ClientGenerator* generator = new ClientGenerator;

    // Déplacer l'objet dans un thread séparé
    generator->moveToThread(thread);

    // Connexion pour démarrer et arrêter proprement
    QObject::connect(thread, &QThread::started, generator, &ClientGenerator::start);
    QObject::connect(qApp, &QCoreApplication::aboutToQuit, generator, &ClientGenerator::stop);
    QObject::connect(qApp, &QCoreApplication::aboutToQuit, thread, &QThread::quit);
    QObject::connect(thread, &QThread::finished, generator, &QObject::deleteLater);
    QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    // Lancer le thread
    thread->start();
}

void testTm(){
    testInitTM();

    Client cl1, cl2, cl3, cl4, cl5;
    Product pr1, pr2, pr3;
    Cmd cm1, cm2, cm3, cm4, cm5, cm6;

    Client::tms.clear();
    Product::tms.clear();
    Cmd::tms.clear();

    comm();

    bg();

    if (Client::tms.all().empty())
    {
        cl1.name = "Olivier TAMBO";
        cl1.email = "dhondhon@gmail.com";
        cl2.name = "Michel TAMBO";
        cl2.email = "michael@gmail.com";
        cl3.name = "Patie TAMBO";
        cl3.email = "ball@gmail.com";
        cl4.name = "Olivier TB";
        cl4.email = "tb@gmail.com";
        cl5.name = "Annie TAMBO";
        cl5.email = "bom@gmail.com";
        //
        cl1.save();
        cl2.save();
        cl3.save();
        cl4.save();
        cl5.save();
        cl4.name = "Olivier TAMBO";
        cl4.save();
        cl5.del();
        //
        cl1.friends = { &cl2, &cl3 };
        cl1.friends += cl4;
        cl1.meta += {
                     {"T", 12},
                     {"T2", 12},
                     {"T3", 12},
                     };
        //
        cl1.save();
    }
    if (Product::tms.all().empty())
    {
        pr1.name = "Poulet";
        pr2.name = "Poisson";
        pr3.name = "Porc";
        //
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
    Client ct = Cmd::tms.all().first().client;
    Log::d("_client: \n" + ct.data());

    auto filter1 = Client::tms.with(cl).filter(cl._id > 0)
                       .order(+cl.name)
                       .group(cl.name).filter(cl._id.count() == 2);
    Log::d("filter1: \n" + filter1.data());
}

int main(int argc, char *argv[])
{
    testTm();

    QGuiApplication app(argc, argv);

    qmlRegisterType<ClientViewModel>("models", 1, 0, "ClientViewModel");

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("TestMingw", "Main");

    return app.exec();
}


























