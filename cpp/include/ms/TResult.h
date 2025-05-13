#pragma once

#include <string>
#include <vector>
#include <optional>
#include "core/Tob.hpp"

/*
 * T query Result
 *
 */
class TqResult {
public:
    enum class Status { DONE, ERROR, NOT_FOUND };
public:
    Status status = Status::DONE;
    std::string data = "";
};
