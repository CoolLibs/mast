#pragma once

#include <string>
#include <utility>

namespace mast {

struct Operator {
    std::string _symbol;
    bool        _right_associative;
    int8_t      _precedence;
};

} // namespace mast