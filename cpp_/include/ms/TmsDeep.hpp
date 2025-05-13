#pragma once

#include "Tms.h"
#include "field/TField.h"

#include "core/Tob.hpp"
#include "field/Tx.h"

#include "TmsFilter.hpp"

class TmsDeep : public Tob
{
public:
    static bool exists(Tclass* _modelClass);
    static bool clear(Tclass* _modelClass);
    static std::string read(Tclass* _modelClass, std::shared_ptr<TFilterBuilder> builder);
    static int64_t lastInsertRowId(Tclass* _modelClass);
    static void notifyChange(Tclass* _modelClass, bool onCreate, bool onUpdate, bool onDelete);
    static bool insertData(Tclass* _modelClass, const std::string j);
    static bool updateData(Tclass* _modelClass, const std::string jsonData, const std::string key);
    static std::string join(const std::vector<std::string>& vec, const std::string& delim);
    static bool deleteData(Tclass* _modelClass, const std::string jsonData, const std::string key);
    static void addObserver(Tclass* _modelClass, const std::shared_ptr<TModelObserver>& observer);
    static void removeObserver(Tclass* _modelClass, const std::shared_ptr<TModelObserver>& observer);
};



template <typename... Ts>
Tlist<Ts...> Tms<Ts...>::filter(std::shared_ptr<TupleType> tuplet, Tx& tx) {
    apply(*tuplet, tx);

    _builder->joins({
        { "INNER", tx.targetModel(), tx.toString() }
        });

    return filter();
}
template <typename... Ts>
Tlist<Ts...> Tms<Ts...>::filter(T& item, Tx& tx) {
    fillTx(tx, name(), item.clazz().getFields());
    if (tx.isAggr())
    {
        _builder->having(tx.toString());
    }
    else
    {
        _builder->where({
            {"", "", tx.toString() }
            });
    }

    return filter();
}
template <typename... Ts>
void Tms<Ts...>::fillTx(Tx& x, std::string modelName, AnyList modelFields)
{
    TmsFilter::fillTx(x, modelName, modelFields);
}
template <typename... Ts>
template <typename Tuple, std::size_t... Is>
void Tms<Ts...>::applyImpl(Tuple& tuple, Tx& tx, std::index_sequence<Is...>) {
    (void)std::initializer_list<int>{
        (
            [&]() {
                auto& elt = std::get<Is>(tuple).get();
                using Ti = std::decay_t<decltype(elt)>;
                auto name = (Tms<Ti>()).name();
                auto fields = elt.clazz().getFields();

                fillTx(tx, name, fields);
            }(),
                0
                )...
    };
}
template <typename... Ts>
void Tms<Ts...>::apply(TupleType& tuple, Tx& tx) {
    applyImpl(tuple, tx, std::index_sequence_for<Ts...>{});
}
