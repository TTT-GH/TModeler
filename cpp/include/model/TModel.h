#pragma once

#include <string>

#include "field/TFields.hpp"
#include "ms/Tms.h"
#include "model/TMserializer.h"


#define TMClass Tclass::with(*this)
#define TModelSuper &(TModel::clazz())
#define TMSuper(T) &(T::clazz())

#define TM_SCHEMA(CLASSNAME, PACKAGE, ...) \
private: \
    Tclass _class = TMClass; \
public: \
    static Tms<CLASSNAME> tms; \
    Tclass& clazz() override { \
        return _class.super(TModelSuper).package(PACKAGE).fields(__VA_ARGS__); \
    }

#define TM_MANAGER(CLASSNAME) \
    Tms<CLASSNAME> CLASSNAME::tms;

#define TM_SCHEMA_EXPLICIT(SUPERCLASS, CLASSNAME, PACKAGE, ...) \
private: \
    Tclass _class = TMClass; \
public: \
    static Tms<CLASSNAME> tms; \
    Tclass& clazz() override { \
        return _class.super(SUPERCLASS).package(PACKAGE).fields(__VA_ARGS__); \
    }

#define TM_SERIAL(SERIAL_EXPR) \
protected: \
    TMserial _serializer = SERIAL_EXPR; \
public: \
    Tserial& serial() override { \
        return _serializer; \
    }






template <typename T>
class TModel : public Tob{
    TM_SCHEMA_EXPLICIT(TMSuper(Tob), T, "models.group", TF(id), TF(_id), TF(meta))
    TM_SERIAL(TMserial())

    Tms<T> _tms;

    IntField id;
    IntField _id = init<IntField>().primaryKey().autoIncrement().notNull();
    JsonField meta = init<JsonField>();

    virtual IntField& key() { return _id; }
    virtual std::string keyName() { return TF(_id).first;}

    int save();
    int create();
    int update();
    int del();

    virtual bool isCreated();
    virtual bool saveOnLinking();

    virtual bool isNull();
    virtual void null(bool v);
private:
    bool _null = false;
};
