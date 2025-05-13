#pragma once

#include "Tms.h"
#include "field/TField.h"

#include "ms/TitemCreate.hpp"

#include "core/Tob.hpp"
#include "field/Tx.h"

class TmsFilter : public Tob
{
public:
    static void fillTx(Tx& x, std::string modelName, AnyList modelFields);
    static TqResult query(Tclass* _modelClass, std::string sql);
};


template <typename... Ts>
Tlist<Ts...> Tms<Ts...>::filter()
{
    if (_builder == nullptr)
    {
        _builder = std::make_shared<TFilterBuilder>();
        _builder->from(name());
    }

    return build();
}


template <typename... Ts>
Tlist<Ts...> Tms<Ts...>::filter(Tx& tx)
{
    return _instance != nullptr ? filter(*_instance, tx) : _tuplet != nullptr ? filter(_tuplet, tx) : filter();
}
template <typename... Ts>
Tlist<Ts...> Tms<Ts...>::filter(Tx&& tx)
{
    return _instance != nullptr ? filter(*_instance, tx) : _tuplet != nullptr ? filter(_tuplet, tx) : filter();
}




template <typename... Ts>
Tlist<Ts...> Tms<Ts...>::limit(int count)
{
    return filter();
}




template <typename... Ts>
Tlist<Ts...> Tms<Ts...>::order(Tx& tx)
{
    return order(*_instance, tx);
}
template <typename... Ts>
Tlist<Ts...> Tms<Ts...>::order(T& item, Tx& tx)
{
    fillTx(tx, name(), item.clazz().getFields());

    _builder->orderBy({
        { tx.toString() }
        });

    return build();
}




template <typename... Ts>
template<typename... Args>
Tlist<Ts...> Tms<Ts...>::group(Args&... args)
{
    static_assert((std::is_base_of_v<BaseField, Args> && ...), "All args must derive from BaseField");

    T& item = *_instance;

    // Pour chaque arg, on construit un Tx et on ajoute au builder
    ((
        [&]() {
            Tx tx(&args, Operator::GroupBy);
            fillTx(tx, name(), item.clazz().getFields());
            _builder->addGroupBy(tx.toString());
        }()
            ), ...);

    return build();
}


template <typename... Ts>
Tms<Ts...> Tms<Ts...>::join(JoinType type)
{
    return *this;
}


template <typename... Ts>
TqResult Tms<Ts...>::query(std::string sql)
{
    return TmsFilter::query(modelClass(), sql);
}
