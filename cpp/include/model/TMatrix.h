#pragma once

#include <string>

#include "field/TFields.hpp"
#include "ms/Tms.h"
#include "model/TMserializer.h"
#include "model/TModel.hpp"

/*
 * Def de la matrix de recherche
 * basé sur l'AQR
 */
template <typename T>
class TMatrix : public TModel<T> {

    // Definition of data field
    ModelField<T> cell = init<ModelField<T>>().onDelete(TF::CASCADE);

    // Definition of node children
    ModelField<TMatrix<T>> lt = init<ModelField<TMatrix<T>>>().onDelete(TF::CASCADE);
    ModelField<TMatrix<T>> rt = init<ModelField<TMatrix<T>>>().onDelete(TF::CASCADE);
    ModelField<TMatrix<T>> lb = init<ModelField<TMatrix<T>>>().onDelete(TF::CASCADE);
    ModelField<TMatrix<T>> rb = init<ModelField<TMatrix<T>>>().onDelete(TF::CASCADE);

    // Coordonées
    FloatField x;
    FloatField y;
};
