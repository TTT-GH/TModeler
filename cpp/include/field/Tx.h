#pragma once

#include <any>
#include <string>

#include "core/Tob.hpp"

using ValueVariant = std::variant<int, double, std::string>;

enum class Operator {
    NONE,
    GreaterThan,   // ">"
    LessThan,      // "<"
    Equal,         // "="
    NotEqual,      // "!="
    In,            // "IN" >>=
    Like,          // "LIKE" %
    GreaterThanEqual,  // ">="
    LessThanEqual,     // "<="
    Between,
    IsNull,
    And,
    Or,
    Not,

    //Order
    Asc,
    Desc,

    //Group
    GroupBy,

    // Agrégation
    Max,
    Min,
    Avg,
    Sum,
    Count,
    CountDistinct,
};

class Tx
{
public:
    enum class Type {WHERE, JOIN, AGGR};
public:
    BaseField* field = nullptr;
    Operator op = Operator::NONE;
    ValueVariant value;
    std::vector<ValueVariant> values;
    std::string fieldKey = "";
    Tx* v1 = nullptr;
    Tx* v2 = nullptr;
    std::string _targetModel = "";

    Tx(BaseField* f, Operator o);
    Tx();

    Type type = Type::WHERE;

    std::string opToString() const;

    void notify(BaseField* bf, std::string targetModel, std::string key);

    std::string targetModel() const;

    std::string toString() const;

    bool isJoining() const;

    bool isAggr() const;

    bool empty() const;

    Tx operator&&(Tx&& other);

    Tx operator||(Tx&& other);

    Tx operator!();
};

std::string vectorToString(const std::vector<std::string>& vec);
std::string vectorToString(const std::vector<double>& vec);
std::string vectorToString(const std::vector<int>& vec);
