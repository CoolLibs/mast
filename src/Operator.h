#pragma once

#include <string>
#include <utility>

namespace mast {

struct OperatorProperties {
    std::string _symbol;
    bool        _right_associative;
    int8_t      _precedence;
};

class Operator {
public:
    explicit Operator(OperatorProperties properties)
        : _properties(std::move(properties)) {}

    [[nodiscard]] auto is_right_associative() const -> bool { return _properties._right_associative; };
    [[nodiscard]] auto get_symbol() const -> std::string { return _properties._symbol; };
    [[nodiscard]] auto get_precedence() const -> int8_t { return _properties._precedence; };

private:
    OperatorProperties _properties{};
};

} // namespace mast
