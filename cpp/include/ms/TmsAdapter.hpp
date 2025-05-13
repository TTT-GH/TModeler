#pragma once

#include "core/Tob.hpp"

class TmsAdapter : public Tob
{
public:
    static bool setup(Tclass* modelClass);
};
