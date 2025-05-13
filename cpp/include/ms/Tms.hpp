#pragma once

#include "Tms.h"
#include "field/TField.h"

#include "ms/TitemCreate.hpp"
#include "ms/TitemDelete.hpp"
#include "ms/TitemUpdate.hpp"
#include "ms/TitemLoad.hpp"

#include "TmsAdapter.hpp"
#include "TmsCrud.hpp"
#include "TmsDeep.hpp"
#include "TmsFilter.hpp"
#include "TmsObserver.hpp"



template <typename... Ts>
template <typename... NewTypes>
Tms<Ts..., NewTypes...> Tms<Ts...>::with(Ts&... ts, NewTypes&... args) {
    auto newTms = Tms<Ts..., NewTypes...>();

    newTms._builder = std::make_shared<TFilterBuilder>();
    newTms._builder->from(name());

    newTms._tuplet = std::make_shared<std::tuple<std::reference_wrapper<Ts>..., std::reference_wrapper<NewTypes>...>>(
        std::ref(ts)..., std::ref(args)...);

    return newTms;
}
template <typename... Ts>
Tms<Ts...> Tms<Ts...>::with(T& t)
{
    _builder = std::make_shared<TFilterBuilder>();
    _builder->from(name());
    _instance = &t;
    return *this;
}


template <typename... Ts>
void Tms<Ts...>::prepare()
{
    if (_isReady){ return;}

    if (_instance==nullptr)
    {
        _instance = new T();
    }
    if (_modelClass == nullptr)
    {
        _modelClass = &_instance->clazz();
    }

    setup(_modelClass);

    initCallbacks();
}

template <typename... Ts>
bool Tms<Ts...>::exists() {
    prepare();
    return TmsDeep::exists(_modelClass);
}

// Get the model's class
template <typename... Ts>
Tclass* Tms<Ts...>::modelClass() {
    return _modelClass;
}

// Get the model's name
template <typename... Ts>
std::string Tms<Ts...>::name() {
    prepare();

    return _modelClass->getModelName();
}

// Get the model's db name
template <typename... Ts>
std::string Tms<Ts...>::dbId() {
    prepare();

    return _modelClass->geTdb();
}

template <typename... Ts>
bool Tms<Ts...>::clear()
{
    if (exists())
    {
        bool result = TmsDeep::clear(_modelClass);
        if (result)
        {
            _isReady = false;
            return result;
        }
    }
    return false;
}

template <typename... Ts>
Tlist<Ts...> Tms<Ts...>::build()
{
    /*
     * consequence des build intermedière :
     * Il y a des build redondant tout le temps
     * Donner un possibiliter de s'en passer et de build qu'à la fin
     *
     * Une sorte de build à postériori
     *
     */

    prepare();

    return TitemLoad<Ts...>::get(std::make_shared<Tms<Ts...>>(*this), _builder);
}

template <typename... Ts>
void Tms<Ts...>::setup(Tclass* modelClass)
{
    _isReady = TmsAdapter::setup(modelClass);
}
