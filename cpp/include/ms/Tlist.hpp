#include "ms/Tlist.h"

#include "Tms.hpp"

template <typename... Ts>
Tlist<Ts...>::Tlist(std::shared_ptr<Tms<Ts...>> tms) : std::vector<BaseType>(), _tms(tms){}

template <typename... Ts>
Tlist<Ts...>::Tlist(std::shared_ptr<Tms<Ts...>> tms, const std::vector<BaseType>& vec) : std::vector<BaseType>(vec), _tms(tms) {}

template <typename... Ts>
void Tlist<Ts...>::add(const ValueType& value) {
    this->push_back(value);
}

template <typename... Ts>
typename Tlist<Ts...>::ValueType& Tlist<Ts...>::get(size_t index) {
    if (index >= this->size())
        throw std::out_of_range("Index out of range");
    return (*this)[index];
}

template <typename... Ts>
void Tlist<Ts...>::set(size_t index, const ValueType& value) {
    if (index >= this->size())
        throw std::out_of_range("Index out of range");
    (*this)[index] = value;
}

template <typename... Ts>
void Tlist<Ts...>::remove(size_t index) {
    if (index >= this->size())
        throw std::out_of_range("Index out of range");
    this->erase(this->begin() + index);
}

template <typename... Ts>
bool Tlist<Ts...>::empty() const {
    return BaseVector::empty();
}

template <typename... Ts>
void Tlist<Ts...>::clear() {
    BaseVector::clear();
}




template <typename... Ts>
bool Tlist<Ts...>::remove(const ValueType& value) {
    auto it = std::find(this->begin(), this->end(), value);
    if (it != this->end()) {
        this->erase(it);
        return true;
    }
    return false;
}

template <typename... Ts>
bool Tlist<Ts...>::contains(const ValueType& value) const {
    return std::find(this->begin(), this->end(), value) != this->end();
}

template <typename... Ts>
int Tlist<Ts...>::indexOf(const ValueType& value) const {
    auto it = std::find(this->begin(), this->end(), value);
    if (it != this->end())
        return static_cast<int>(std::distance(this->begin(), it));
    return -1;
}

template <typename... Ts>
int Tlist<Ts...>::lastIndexOf(const ValueType& value) const {
    auto it = std::find(this->rbegin(), this->rend(), value);
    if (it != this->rend())
        return static_cast<int>(this->size() - 1 - std::distance(this->rbegin(), it));
    return -1;
}

template <typename... Ts>
size_t Tlist<Ts...>::size() const {
    return BaseVector::size();
}

template <typename... Ts>
Tlist<Ts...> Tlist<Ts...>::subList(size_t fromIndex, size_t toIndex) const {
    if (fromIndex > toIndex || toIndex > this->size())
        throw std::out_of_range("Invalid sublist range");
    return Tlist<Ts...>(this->begin() + fromIndex, this->begin() + toIndex);
}



template <typename... Ts>
Tlist<Ts...> Tlist<Ts...>::filter(const std::function<bool(const typename Tlist<Ts...>::ValueType&)>& predicate) const {
    /* T T T ::: IMPORTANT */
    /*
    Tlist<T> result = Tlist<T>(_tms);
    for (const auto& item : *this) {
        if (predicate(item)) {
            result.add(item);
        }
    }
    return result;*/
    return *this;
}




template <typename... Ts>
Tlist<Ts...> Tlist<Ts...>::filter(Tx&& tx) // start by dispatching T H I S
{
    return _tms->filter(tx);
}


template <typename... Ts>
Tlist<Ts...> Tlist<Ts...>::order(Tx&& tx)
{
    return _tms->order(tx);
}
template <typename... Ts>
template<typename... Args>
Tlist<Ts...> Tlist<Ts...>::group(Args&... args)
{
    static_assert((std::is_base_of_v<BaseField, Args> && ...), "All args must derive from BaseField");
    return _tms->group(args...);
}

template <typename... Ts>
Tlist<Ts...> Tlist<Ts...>::build()
{
    return _tms->build();
}

/*
template <typename... Ts>
Tlist<Ts...> Tlist<Ts...>::group(Tx&& tx)
{
    return _tms->orderBy(tx);
}

template <typename... Ts>
Tlist<Ts...> Tlist<Ts...>::orderBy(Tx&& tx)
{
    return _tms->orderBy(tx);
}*/


template <typename... Ts>
std::string Tlist<Ts...>::data()
{
    return Tob::data<T>(*this);
}

template <typename... Ts>
typename Tlist<Ts...>::ValueType Tlist<Ts...>::first_cp()
{
    T obj;
    obj.null(true);
    return empty() ? obj : get(0);
}
template <typename... Ts>
typename Tlist<Ts...>::ValueType& Tlist<Ts...>::first()
{
    T obj;
    obj.null(true);
    return empty() ? obj : get(0);
}
template <typename... Ts>
typename Tlist<Ts...>::ValueType* Tlist<Ts...>::last()
{
    return empty() ? nullptr : &get(size() - 1);
}
