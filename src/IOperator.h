#pragma once

#include <cstdint>
#include <string>

namespace mast {

class IOperator {
public:
    [[nodiscard]] virtual auto is_right_associative() const -> bool    = 0;
    [[nodiscard]] virtual auto get_symbol() const -> std::string       = 0;
    [[nodiscard]] virtual auto get_precedence() const -> int8_t        = 0;
    [[nodiscard]] virtual auto compare_precedence(IOperator* o) -> int = 0;
};

} // namespace mast