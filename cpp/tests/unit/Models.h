#pragma once
#include <model/TModel.hpp>

class Client : public TModel<Client> {
private:
    Tclass _class = TMClass;
public:
    TextField name;

    static Tms<Client> tms;

    Tclass& clazz() override {
        return _class.super(TModelSuper).package("models.shop").fields(TF(name));
    }
};
Tms<Client> Client::tms;

class Product : public TModel<Product> {
private:
    Tclass _class = TMClass;
public:
    TextField name;

    static Tms<Product> tms;

    Tclass& clazz() override {
        return _class.super(TModelSuper).package("models.shop").fields(TF(name));
    }
};
Tms<Product> Product::tms;

class Cmd : public TModel<Cmd> {
private:
    Tclass _class = TMClass;
public:
    ModelField<Client> client;
    ModelField<Product> product;

    static Tms<Cmd> tms;

    Tclass& clazz() override {
        return _class.super(TModelSuper).package("models.shop").fields(TF(client), TF(product));
    }
};
Tms<Cmd> Cmd::tms;


namespace Expr {
    inline Client cl{};
    inline Product pr{};
    inline Cmd cm{};
}

using Expr::cl;
using Expr::pr;
using Expr::cm;
