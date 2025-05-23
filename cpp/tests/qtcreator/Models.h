#ifndef MODELS_H
#define MODELS_H

#include <QObject>

#include <model/TModel.hpp>

class Client : public TModel<Client> {
    TM_SCHEMA(Client, "models.shops", TF(name), TF(email), TF(friends))

    TextField name;
    TextField email;
    ListField<Client> friends;
};

class Product : public TModel<Product> {
    TM_SCHEMA(Product, "models.shops", TF(name))

    TextField name;
};

class Cmd : public TModel<Cmd> {
    TM_SCHEMA(Cmd, "models.shops", TF(client), TF(product))

    ModelField<Client> client;
    ModelField<Product> product;
};


namespace Expr {
inline Client cl{};
inline Product pr{};
inline Cmd cm{};
}

using Expr::cl;
using Expr::pr;
using Expr::cm;


void sleep(long dur=-1);
void testInitTM();

#endif // MODELS_H
