#pragma once
#include <string>
#include <any>
#include <sstream>
#include <iostream>
#include <map>

#include <vector>

#include "Ttable.h"


class TModelObserver {
public:
    virtual ~TModelObserver() {}

    virtual void onModelChange() = 0;
    virtual void onSave() = 0;
    virtual void onCreate() = 0;
    virtual void onUpdate() = 0;
    virtual void onDelete() = 0;
};

