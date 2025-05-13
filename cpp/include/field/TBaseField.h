#pragma once

#include <any>
#include <string>

#include "core/Tob.h"
#include "field/Tx.h"

// define TModel Fields
#define TF(k) (k >> #k)

// Enumération des types possibles pour un champ
enum class TFtype {
    INTEGER,
    VARCHAR,
    TEXT,
    REAL,
    BLOB
};

/*
 * Gere tous les constantes des fields
 *
 */
enum class TF {
    NONE,
    PRIMARY_KEY,
    AUTOINCREMENT,
    NOT_NULL,
    UNIQUE,
    CHECK,
    FOREIGN_KEY, 
    DEFAULT,
    INDEX,
    CASCADE,
    SET_NULL,
    NO_ACTION,
    RESTRICT,
    SET_DEFAULT,
    CURRENT_TIMESTAMP,
    DATE,
    DATE_TIME
};

// Classe qui gère les contraintes
class TFconstraints {
public:
    void addIfNotExist(TF v);
    void removeIfExist(TF v);
    std::string toString() const;

    // Méthodes de vérification des contraintes
    bool isPrimaryKey() const;
    bool isAutoIncrement() const;
    bool isNotNull() const;
    bool isUnique() const;
    bool isCheck() const;
    bool isForeignKey() const;
    bool isDefault() const;
    bool isIndexed() const;

    std::vector<TF> _all;


    std::string str();
};

std::string tf_str(TFtype type);

std::string tf_str(TF value);

class BaseField : public Tob {
protected:
    std::any _nullValue;
    std::any _value;
    TFtype _type;
    int _maxLen = -1;

    Tclass* _targetModel_;
    Tclass _targetModel;
    std::string _targetField = "";
    TFconstraints _constraints;
    TF _onDelete = TF::NONE;

public:
    BaseField(){}

    virtual std::any& refValue();
    virtual std::any getValue() const;
    virtual bool empty() const;
    virtual void setValue(const std::any& v);
    virtual TFtype getType() const;
    virtual int getMaxLen() const;
    virtual TFconstraints getConstraints() const;
    virtual TF getOnDelete() const;
    virtual Tclass getTargetModel();
    virtual std::string getTargetField() const;

    std::pair < std::string, std::any> field(std::string k);
    std::pair<std::string, std::any> operator>>(const std::string& k);

    static int NULL_INT;
    static double NULL_FLOAT;
    static std::string NULL_STRING;

    Tx aggr;

    Tx isNull();
    std::string targetField();
};
