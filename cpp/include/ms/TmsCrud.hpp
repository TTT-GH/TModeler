#pragma once

#include "Tms.h"
#include "field/TField.h"

#include "ms/TitemCreate.hpp"
#include "ms/TitemDelete.hpp"
#include "ms/TitemUpdate.hpp"





template <typename... Ts>
Tlist<Ts...> Tms<Ts...>::all()
{
    T i;
    return with(i).filter();
}
template <typename... Ts>
Tlist<Ts...> Tms<Ts...>::get(KeysType& keys)
{
    T i;
    return with(i).filter(i._id >>= keys);
}
template <typename... Ts>
typename Tms<Ts...>::T Tms<Ts...>::get(int k)
{
    return getByKey(k);
}
template <typename... Ts>
typename Tms<Ts...>::T Tms<Ts...>::getById(int k)
{
    prepare();
    T i;
    return with(i).filter(i.id == k).first_cp();
}
template <typename... Ts>
typename Tms<Ts...>::T Tms<Ts...>::getByKey(int k)
{
    prepare();
    T i;
    return with(i).filter(i.key() == k).first_cp();
}



template <typename... Ts>
int Tms<Ts...>::save(std::vector<T> instances)
{
    return update(instances);
}
template <typename... Ts>
int Tms<Ts...>::create(std::vector<T> instances)
{
    return create(Tlist<T>(std::make_shared<Tms<T>>(*this), instances));
}
template <typename... Ts>
int Tms<Ts...>::update(std::vector<T> instances)
{
    return update(Tlist<T>(std::make_shared<Tms<T>>(*this), instances));
}
template <typename... Ts>
int Tms<Ts...>::del(std::vector<T> instances)
{
    return del(Tlist<T>(std::make_shared<Tms<T>>(*this), instances));
}





template <typename... Ts>
template <typename... Ts2>
int Tms<Ts...>::save(T& first, Ts2&... rest) {
    Tlist<T> instances(std::make_shared<Tms<T>>(*this));
    instances.push_back(first);
    (instances.push_back(rest), ...);
    return save(instances);
}
template <typename... Ts>
template <typename... Ts2>
int Tms<Ts...>::create(T* first, Ts2*... rest) {
    Tlist<T*> instances;
    //instances.tms(std::make_shared<Tms<T>>(*this));
    instances.push_back(first);
    (instances.push_back(rest), ...);
    return create(instances);
}
template <typename... Ts>
template <typename... Ts2>
int Tms<Ts...>::update(T& first, Ts2&... rest) {
    Tlist<T> instances(std::make_shared<Tms<T>>(*this));
    instances.push_back(first);
    (instances.push_back(rest), ...);
    return update(instances);
}
template <typename... Ts>
template <typename... Ts2>
int Tms<Ts...>::del(T& first, Ts2&... rest) {
    Tlist<T> instances(std::make_shared<Tms<T>>(*this));
    instances.push_back(first);
    (instances.push_back(rest), ...);
    return del(instances);
}






template <typename... Ts>
int Tms<Ts...>::save(Tlist<T> instances)
{
    return create(instances);
}
template <typename... Ts>
int Tms<Ts...>::create(Tlist<T*>& instances)
{
    prepare();
    TitemCreate<Ts...>::create(std::make_shared<Tms<T>>(*this), _builder, instances);
    return 0;
}
template <typename... Ts>
int Tms<Ts...>::update(Tlist<T> instances)
{
    prepare();
    TitemUpdate<Ts...>::put(std::make_shared<Tms<T>>(*this), _builder, instances);
    return 0;
}
template <typename... Ts>
int Tms<Ts...>::del(Tlist<T> instances)
{
    prepare();
    TitemDelete<Ts...>::del(std::make_shared<Tms<T>>(*this), _builder, instances);
    return 0;
}
