#pragma once

#include <any>
#include <string>
#include <chrono>
#include <vector>

#include "field/TField.hpp"
#include "field/TIntField.hpp"
#include "ms/Tms.hpp"

template <typename T>
class ModelField : public IntFieldBase<ModelField<T>> {
protected:
    std::shared_ptr<Tms<T>> _tms = nullptr;
public:
    ModelField() : IntFieldBase<ModelField<T>>()
    {
        TField<ModelField, int>::foreignKey();

        // Bloc is necessary to avoid self Model bounce
        static thread_local bool alreadyIn = false;
        if (!alreadyIn) {
            try {
                alreadyIn = true;
                BaseField::_targetModel_ = Tob::instance<T>().clazz3();
                BaseField::_targetField = Tob::instance<T>().keyName();
            }
            catch (...) {}
            alreadyIn = false;
        }
    }

    std::shared_ptr<Tms<T>> tms()
    {
        if (_tms==nullptr)
        {
            _tms = std::make_shared<Tms<T>>();
        }
        return _tms;
    }

    T model() {
        return tms()->get(IntFieldBase<ModelField<T>>::get());
    }

    void set(T& v) {
        if (v.saveOnLinking())
        {
            v.save();
        }
        if(v.isCreated())
        {
            IntFieldBase<ModelField<T>>::set(v.key().get());
        }
    }

    virtual ModelField& defaults(T v) {
        set(v);
        return *this;
    }

    virtual ModelField& onDelete(TF v) {
        IntFieldBase<ModelField<T>>::onDelete(v);
        return *this;
    }

    // operators
    ModelField& operator=(T& v) {
        set(v);
        return *this;
    }
    operator T() {
        return model();
    }


    Tx operator==(T& item) {
        Tx x(this, Operator::Equal);
        //x._targetModel = Tms<T>().name();
        x.value = Tms<T>().name() + "." + item.keyName();
        return x;
    }

    Tx operator>(const T& val) {
        Tx x(this, Operator::GreaterThan);
        x.value = val;
        return x;
    }
    Tx operator<(const T& val) {
        Tx x(this, Operator::LessThan);
        x.value = val;
        return x;
    }
    Tx operator!=(const T& val) {
        Tx x(this, Operator::NotEqual);
        x.value = val;
        return x;
    }
    Tx operator>=(const T& val) {
        Tx x(this, Operator::GreaterThanEqual);
        x.value = val;
        return x;
    }
    Tx operator<=(const T& val) {
        Tx x(this, Operator::LessThanEqual);
        x.value = val;
        return x;
    }
};
