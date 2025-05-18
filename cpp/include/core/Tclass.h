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
    AnyList _fields;
    std::string _package = "";
    std::string _db = "";


    std::type_index _type;
    /* for another time
    std::shared_ptr<Tclass> _super = nullptr;
    */
    Tclass* _superClass = nullptr;

public:
    /*
    Tclass(std::type_index type, std::shared_ptr<Tclass> super = nullptr);*/

    Tclass();
    Tclass(Tob& inst, Tclass* sup = nullptr);
    Tclass(Tob& inst);
    static Tclass with(Tob& instance);

    const std::type_index& type() const;

    Tclass* super() const;
    Tclass& super(Tclass* v);



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

    std::string name() const;

    std::string getPackage() const;

    std::string geTdb() const;

    std::string getModelName() const;

    bool equals(Tclass* cls) const;


    bool operator==(Tclass& cls) const;

    bool operator!=(Tclass&& cls) const;

private:
    std::string name(const std::string& rawName) const;
};


#endif // TCLASS_H
