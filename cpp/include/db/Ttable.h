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

    std::string toScript() const;

    std::string toForeignScript() const;

    TtableField& name(const std::string& v);

    TtableField& type(const std::string& v);

    TtableField& defaultValue(const std::any& v);

    TtableField& constraints(const std::string& v);

    TtableField& maxlen(int v);

    TtableField& targetTable(const std::string& v);

    TtableField& targetField(const std::string& v);

    TtableField& onDelete(const std::string& v);

private:
    std::string _name;
    std::string _type;
    std::any _defaultValue;
    std::string _constraints;
    int _maxlen;
    std::string _targetTable;
    std::string _targetField;
    std::string _onDelete;

    std::string formatDefaultValue(const std::any& value) const;
};

class TtableDriver {
public:
    TtableDriver();

    TtableDriver(const std::string& name, const std::vector<TtableField>& fields = {}, const std::vector<std::string>& primaryKeys = {});

    std::string toScript() const;

    void addField(const TtableField& field);

    std::string getName() const;

private:
    std::string name;
    std::vector<TtableField> fields;
    std::vector<std::string> primaryKeys;

    std::string join(const std::vector<std::string>& elements, const std::string& delimiter) const;
};

class Ttable {
    std::vector<std::shared_ptr<TModelObserver>> _observers;

public:
    std::unique_ptr<TtableDriver> _driver;

    Ttable(const std::string& name, const std::vector<TtableField>& fields = {},
        const std::vector<std::string>& primaryKeys = {});

    void addObserver(const std::shared_ptr<TModelObserver>& observer);

    void removeObserver(const std::shared_ptr<TModelObserver>& observer);
    
    void notifyChange(KeysType keys);

    void notifySave(KeysType keys);

    void notifyCreate(KeysType keys);

    void notifyUpdate(KeysType keys);

    void notifyDelete(KeysType keys);

    void notifyChange(KeysType keys, bool onCreate, bool onUpdate, bool onDelete);
};
