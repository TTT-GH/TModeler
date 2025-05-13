#pragma once
#include <string>
#include <any>
#include <sstream>
#include <iostream>
#include <memory>

#include <vector>

#include "TdbObserver.h"

class TModelObserver;

/*
 * About Table Field
 */
class TtableField {
public:
    TtableField(const std::string& name, const std::string& type,
        const std::any& defaultValue = {}, const std::string& constraints = "",
        int maxlen = 0, const std::string& targetTable = "", const std::string& targetField = "",
        const std::string& onDelete = "")
        : _name(name), _type(type), _defaultValue(defaultValue), _constraints(constraints),
        _maxlen(maxlen), _targetTable(targetTable), _targetField(targetField), _onDelete(onDelete) {}

    std::string toScript() const {
        std::ostringstream script;
        script << _name << " " << _type;

        if (_maxlen > 0) {
            script << "(" << _maxlen << ")";
        }

        if (!_constraints.empty()) {
            script << " " << _constraints;
        }

        if (_defaultValue.has_value()) {
            script << " DEFAULT " << formatDefaultValue(_defaultValue);
        }

        return script.str();
    }

    std::string toForeignScript() const {
        std::ostringstream script;

        if (!_targetTable.empty() && !_targetField.empty()) {
            script << "   FOREIGN KEY (" << _name << ")"
                << " REFERENCES " << _targetTable << "(" << _targetField << ")";

            if (!_onDelete.empty()) {
                script << " ON DELETE " << _onDelete;
            }
        }

        return script.str();
    }

    TtableField& name(const std::string& v) {
        _name = v;
        return *this;
    }

    TtableField& type(const std::string& v) {
        _type = v;
        return *this;
    }

    TtableField& defaultValue(const std::any& v) {
        _defaultValue = v;
        return *this;
    }

    TtableField& constraints(const std::string& v) {
        _constraints = v;
        return *this;
    }

    TtableField& maxlen(int v) {
        _maxlen = v;
        return *this;
    }

    TtableField& targetTable(const std::string& v) {
        _targetTable = v;
        return *this;
    }

    TtableField& targetField(const std::string& v) {
        _targetField = v;
        return *this;
    }

    TtableField& onDelete(const std::string& v) {
        _onDelete = v;
        return *this;
    }

private:
    std::string _name;
    std::string _type;
    std::any _defaultValue;
    std::string _constraints;
    int _maxlen;
    std::string _targetTable;
    std::string _targetField;
    std::string _onDelete;

    std::string formatDefaultValue(const std::any& value) const {
        if (value.type() == typeid(std::string)) {
            return "'" + std::any_cast<std::string>(value) + "'";
        }
        else if (value.type() == typeid(int)) {
            return std::to_string(std::any_cast<int>(value));
        }
        else if (value.type() == typeid(double)) {
            return std::to_string(std::any_cast<double>(value));
        }
        else if (value.type() == typeid(bool)) {
            return std::any_cast<bool>(value) ? "TRUE" : "FALSE";
        }
        return "";
    }
};

class TtableDriver {
public:
    TtableDriver() {}

    TtableDriver(const std::string& name, const std::vector<TtableField>& fields = {}, const std::vector<std::string>& primaryKeys = {})
        : name(name), fields(fields), primaryKeys(primaryKeys) {}

    std::string toScript() const {
        std::ostringstream script;
        script << "CREATE TABLE " << name << " (\n";

        for (size_t i = 0; i < fields.size(); ++i) {
            script << "   " << fields[i].toScript();
            if (i != fields.size() - 1) {
                script << ",\n";
            }
        }

        if (primaryKeys.size() > 1) {
            script << ",\n   PRIMARY KEY (" << join(primaryKeys, ", ") << ")";
        }

        std::vector<std::string> foreignKeys;
        for (const auto& field : fields) {
            std::string foreignScript = field.toForeignScript();
            if (!foreignScript.empty()) {
                foreignKeys.push_back(foreignScript);
            }
        }

        for (size_t i = 0; i < foreignKeys.size(); ++i) {
            script << ",\n" << foreignKeys[i];
        }

        script << "\n);";
        return script.str();
    }

    void addField(const TtableField& field) {
        fields.push_back(field);
    }

    std::string getName() const
    {
        return name;
    }

private:
    std::string name;
    std::vector<TtableField> fields;
    std::vector<std::string> primaryKeys;

    std::string join(const std::vector<std::string>& elements, const std::string& delimiter) const {
        std::ostringstream os;
        for (size_t i = 0; i < elements.size(); ++i) {
            os << elements[i];
            if (i != elements.size() - 1) {
                os << delimiter;
            }
        }
        return os.str();
    }
};

class Ttable {
    std::vector<std::shared_ptr<TModelObserver>> _observers;

public:
    std::unique_ptr<TtableDriver> _driver;

    Ttable(const std::string& name, const std::vector<TtableField>& fields = {}, 
        const std::vector<std::string>& primaryKeys = {})
    {
        _driver = std::make_unique<TtableDriver>(name, fields, primaryKeys);
    }

    void addObserver(const std::shared_ptr<TModelObserver>& observer) {
        _observers.push_back(observer);
    }

    void removeObserver(const std::shared_ptr<TModelObserver>& observer) {
        /* T T T ::: IMPORTANT */
        //_observers.erase(std::remove(_observers.begin(), _observers.end(), observer),_observers.end());
    }

    void notifyChange() {
        for (auto obs : _observers) {
            obs->onModelChange();
        }
    }

    void notifySave() {
        for (auto obs : _observers) {
            obs->onSave();
        }
    }

    void notifyCreate() {
        for (auto obs : _observers) {
            obs->onCreate();
            obs->onModelChange();
        }
    }

    void notifyUpdate() {
        for (auto obs : _observers) {
            obs->onUpdate();
            obs->onModelChange();
        }
    }

    void notifyDelete() {
        for (auto obs : _observers) {
            obs->onDelete();
            obs->onModelChange();
        }
    }


    void notifyChange(bool onCreate, bool onUpdate, bool onDelete) {
        if (onCreate) { notifyCreate(); }
        if (onUpdate) { notifyUpdate(); }
        if (onDelete) { notifyDelete(); }
    }
};
