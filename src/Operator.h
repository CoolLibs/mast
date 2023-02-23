#pragma once

#include <string>
#include <utility>

namespace mast {

struct Operator {
    char   _symbol{};
    int8_t _precedence{};
    bool   _right_associative = false;
};

} // namespace mast