#pragma once

#include <iostream>

namespace mast {

struct OperatorConfig {
    const uint8_t _precedence;
    const bool    _rightAssociative;
    const bool    _unary;
};

class Token {
public:
    // ToDo : I think enum is easier to use but should we use variant here ? (enum seems cool)
    enum class Type {
        Unknown,
        Number,
        Operator,
        LeftParen,
        RightParen,
    };

    Token(Type, std::string content, OperatorConfig = {});

public:
    [[nodiscard]] auto get_type() const -> Type { return _type; };
    [[nodiscard]] auto get_content() const -> std::string { return _content; };
    [[nodiscard]] auto get_precedence() const -> uint8_t { return _operator_config._precedence; };

    [[nodiscard]] auto is_operator() const -> bool { return _type == Type::Operator; };
    [[nodiscard]] auto is_unary() const -> bool { return _operator_config._unary; };
    [[nodiscard]] auto is_right_associative() const -> bool { return _operator_config._rightAssociative; };

private:
    const Type           _type;
    const std::string    _content;
    const OperatorConfig _operator_config{};
};

auto operator<<(std::ostream& os, const Token& token) -> std::ostream&
{
    os << token.get_content();
    return os;
}

} // namespace mast