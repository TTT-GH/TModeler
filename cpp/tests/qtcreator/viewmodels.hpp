#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QAbstractListModel>
#include "Models.h"

#include "TVM.hpp"


class ClientItem : public TItem<Client> {
    Q_OBJECT
    TM_QML_ITEM
};


class ClientViewModel : public TViewModel<Client> {
    Q_OBJECT
    TM_QML_VM(Client, ClientItem)

signals:
    void errorOccurred(const QString& message);
    void countChanged();

protected:
    void emit_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>()){
        emit dataChanged(topLeft, bottomRight, roles);
    }
    void emit_errorOccurred(const QString& message){
        emit errorOccurred(message);
    }
    void emit_countChanged(){
        emit countChanged();
    }
};

#endif // VIEWMODEL_H
