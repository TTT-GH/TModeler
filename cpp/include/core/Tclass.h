#ifndef TCLASS_H
#define TCLASS_H

#include <functional>
#include <typeindex>
#include <string>
#include <unordered_map>
#include <iostream>
#include <variant>
#include <any>

using AnyList = std::vector<std::pair<std::string, std::any>>;

class Tob;

class Tclass {
protected:
    Tob& _instance;
    Tclass* _superClass = nullptr;

    AnyList _fields;
    std::string _package = "";
    std::string _db = "";

public:
    static Tclass with(Tob& instance);

    Tclass();

    Tclass(Tob& instance, Tclass* super = nullptr);

    Tclass(Tob& instance);

    Tclass& package(std::string v);

    Tclass& db(std::string v);

    
    template <typename... Args>
    Tclass& fields(Args&&... args) {
        _fields.clear();
        (_fields.emplace_back(args.first, args.second), ...);
        return *this;
    }

    Tclass fields(std::initializer_list < std::pair < std::string, std::any>> fields);

    AnyList getFields(const bool super = true);

    // Compare types between this and another Tclass
    bool equals(const Tclass& other) const;

    // Check if this class descends from another class and return generation distance
    int descendsFrom(const Tclass& parent) const;

    std::type_info const& type() const;

    std::string name() const;

    std::string getPackage() const;

    std::string geTdb() const;

    std::string getModelName() const;

    std::any newInstance() const {return &_instance;}

    Tclass* super() const {return _superClass;}

    Tclass& super(Tclass* v) { _superClass = v; return *this; }

    bool equals(Tclass* cls) const;


    bool operator==(Tclass& cls) const;

    bool operator!=(Tclass&& cls) const;

private:
    std::string name(const std::string& rawName) const;
};


#endif // TCLASS_H
