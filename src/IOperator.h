#pragma once

#include <cstdint>
#include <string>

namespace mast {

class IOperator {
    virtual auto is_right_associative() const -> bool = 0;
    virtual auto get_symbol() const -> std::string = 0;
    virtual auto compare_precedence(IOperator*) const -> int8_t = 0;
};

} // namespace mast