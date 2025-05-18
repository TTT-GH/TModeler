#ifndef TVIEWMODEL_HPP
#define TVIEWMODEL_HPP


#include <QAbstractListModel>
#include <QHash>
#include <QByteArray>
#include <QVariant>
#include <QString>
#include <map>
#include <string>
#include <model/TModel.h>

#include <QAbstractListModel>
#include <QVariant>
#include <QHash>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QByteArray>
#include <QModelIndex>
#include <string>

template<typename T>
class TViewModel : public QAbstractListModel {

public:
    explicit TViewModel(QObject* parent = nullptr)
        : QAbstractListModel(parent)
    {
        m_objects = tms.all();

        auto mc = tms.modelClass();
        auto fields = mc->getFields();

        int role = Qt::UserRole + 1;
        for (const auto& [name, field] : fields) {
            m_roles[role] = name.c_str();
            m_roleNames[name] = role;
            role++;
        }

        observers();
    }

    virtual void observers(){
        tms.onCreate([this](auto keys) {
            QMetaObject::invokeMethod(this, [this, keys]() {
                for (int key : keys) {
                    int index = count();
                    if (index >= 0) {
                        beginInsertRows(QModelIndex(), index, index);
                        m_objects.add(tms.get(key));
                        endInsertRows();
                    }
                }
            }, Qt::QueuedConnection);
        });


        tms.onDelete([this](auto keys) {
            QMetaObject::invokeMethod(this, [this, keys]() {
                for(auto key : keys){
                    int index = m_objects.indexOf(key);
                    if (index >= 0) {
                        beginRemoveRows(QModelIndex(), index, index);
                        m_objects.remove(index);
                        endRemoveRows();
                    }
                }
            }, Qt::QueuedConnection);
        });

        tms.onUpdate([this](auto keys) {
            QMetaObject::invokeMethod(this, [this, keys]() {
                for(auto key : keys){
                    int index = m_objects.indexOf(key);
                    if (index >= 0) {
                        m_objects.get(index).parse(tms.get(key).data());
                        emit dataChanged(this->index(index), this->index(index));
                        refresh();
                    }
                }
            }, Qt::QueuedConnection);
        });
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return static_cast<int>(m_objects.size());
    }

    QVariant data(const QModelIndex& index, int role) const override {
        if (!index.isValid() || index.row() >= static_cast<int>(m_objects.size()))
            return QVariant();

        auto obj = m_objects[index.row()];

        // Trouver le nom du champ à partir du rôle
        auto it = m_roles.find(role);
        if (it == m_roles.end())
            return QVariant();

        const QString& roleName = it.value();

        // Obtenir les données sous forme de JSON
        std::string json = obj.data();

        // Parser le JSON avec QJsonDocument
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(QByteArray::fromStdString(json), &parseError);
        if (parseError.error != QJsonParseError::NoError || !doc.isObject())
            return QVariant();

        QJsonObject objJson = doc.object();

        // Extraire la valeur correspondant au champ demandé
        QJsonValue val = objJson.value(roleName);
        return val.isUndefined() ? QVariant() : val.toVariant();
    }

    QHash<int, QByteArray> roleNames() const override {
        return m_roles;
    }

    Q_INVOKABLE void refresh() {
        beginResetModel();
        Tms<T> tms;
        m_objects = tms.all();
        endResetModel();
    }




    Q_INVOKABLE QVariantMap get(int index) {
        QVariantMap result;

        if (index < 0 || index >= m_objects.size())
            return result;

        T& obj = m_objects[index];
        std::string json = obj.data();

        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(QByteArray::fromStdString(json), &parseError);

        if (parseError.error != QJsonParseError::NoError || !doc.isObject())
            return result;

        QJsonObject jsonObj = doc.object();

        for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
            result[it.key()] = it.value().toVariant();
        }

        return result;
    }

    Q_INVOKABLE bool create(const QVariantMap& data) {
        T obj;

        QJsonObject jsonObj;
        for (auto it = data.begin(); it != data.end(); ++it)
            jsonObj[it.key()] = QJsonValue::fromVariant(it.value());

        QJsonDocument doc(jsonObj);
        obj.parse(doc.toJson(QJsonDocument::Compact).toStdString());

        obj.create();

        return true;
    }

    Q_INVOKABLE bool update(int index, const QVariantMap& data) {
        if (index < 0 || index >= m_objects.size())
            return false;

        T& obj = m_objects[index];

        QJsonObject jsonObj;
        for (auto it = data.begin(); it != data.end(); ++it)
            jsonObj[it.key()] = QJsonValue::fromVariant(it.value());

        QJsonDocument doc(jsonObj);
        obj.parse(doc.toJson(QJsonDocument::Compact).toStdString());

        obj.update();

        return true;
    }

    Q_INVOKABLE bool remove(int index) {
        if (index < 0 || index >= m_objects.size())
            return false;

        T& obj = m_objects[index];

        obj.del();

        return true;
    }

    Q_INVOKABLE int count() const {
        return m_objects.size();
    }



protected:
    Tms<T> tms;
    Tlist<T> m_objects;
    QHash<int, QByteArray> m_roles;
    std::map<std::string, int> m_roleNames;
};


#endif // TVIEWMODEL_HPP
