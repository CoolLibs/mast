#pragma once

#include <string>
#include <utility>

namespace mast {

struct Operator {
    // ToDo : We probably only want a char here.
    std::string _symbol;
    bool        _right_associative;
    int8_t      _precedence;
};

} // namespace mast