#pragma once

#include "model/TModel.h"
#include <iostream>


template <typename T>
int TModel<T>::save() {
    return isCreated() ? update() : create();
}
template <typename T>
int TModel<T>::create()
{
    return _tms.create(static_cast<T*>(this));
}
template <typename T>
int TModel<T>::update()
{
    return _tms.update(static_cast<T&>(*this));
}
template <typename T>
int TModel<T>::del()
{
    return _tms.del(static_cast<T&>(*this));
}

template <typename T>
bool TModel<T>::isCreated()
{
    return !key().empty();
}

template <typename T>
bool TModel<T>::saveOnLinking()
{
    return true;
}

template <typename T>
bool TModel<T>::isNull()
{
    return _null;
}

template <typename T>
void TModel<T>::null(bool v)
{
    _null = v;
}
