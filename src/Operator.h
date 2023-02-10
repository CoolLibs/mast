#pragma once

#include <string>
#include <utility>

namespace mast {

struct Operator {
    char   _symbol;
    bool   _right_associative;
    int8_t _precedence;
};

} // namespace mast