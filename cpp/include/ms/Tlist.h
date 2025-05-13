#pragma once

#include <vector>
#include <stdexcept>

template <typename... Ts>
class Tms;

template <typename... Ts>
class Tlist : public std::vector<
    typename std::conditional<
    sizeof...(Ts) == 1,
    typename std::tuple_element<0, std::tuple<Ts...>>::type,
    std::tuple<Ts...>
    >::type
> {
public:
    using BaseType = typename std::conditional<
        sizeof...(Ts) == 1,
        typename std::tuple_element<0, std::tuple<Ts...>>::type,
        std::tuple<Ts...>
    >::type;

    using BaseVector = std::vector<BaseType>;
    using ValueType = BaseType;
    using T = typename std::tuple_element<0, std::tuple<Ts...>>::type;
private:
    std::shared_ptr<Tms<Ts...>> _tms;

public:
    Tlist() = default;
    Tlist(std::shared_ptr<Tms<Ts...>> tms);
    Tlist(std::shared_ptr<Tms<Ts...>> tms, const std::vector<BaseType>& vec);

    void tms(std::shared_ptr<Tms<Ts...>> tms) { _tms = tms; }

    // Fonctions principales
    void add(const ValueType& value);

    ValueType& get(size_t index);
    //const ValueType& get(size_t index) const;
    void set(size_t index, const ValueType& value);

    void remove(size_t index);
    bool empty() const;
    void clear();

    bool remove(const ValueType& value);
    bool contains(const ValueType& value) const;
    int indexOf(const ValueType& value) const;
    int lastIndexOf(const ValueType& value) const;
    size_t size() const;

    Tlist<Ts...> subList(size_t fromIndex, size_t toIndex) const;

    std::vector<ValueType> vector() const { return *this; }


    Tlist<Ts...> filter(Tx&& x); //simple : where //bi-field : JOIN ON //aggr : HAVING


    
    Tlist<Ts...> order(Tx&& tx);
    template<typename... Args>
    Tlist<Ts...> group(Args&... args);
    /*
    Tlist<Ts...> order(BaseField&... bf);
    Tlist<Ts...> limit(int m);
    Tlist<Ts...> Tms<Ts...>::distinct();*/

    Tlist<Ts...> build();


    Tlist<Ts...> filter(const std::function<bool(const ValueType&)>& predicate) const;


    std::string data();
    ValueType first_cp();
    ValueType& first();
    ValueType* last();
};
