#pragma once

#include <memory>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

#include "Operator.h"

namespace mast {

auto is_a_valid_number(char const& c) -> bool;
auto is_a_variable(std::vector<char> const& variables, char const& c) -> bool;
auto is_an_operator(std::map<char, Operator> const& operators, char const& c) -> bool;

class Token {
public:
    enum class Type {
        Unknown,
        LeftParenthesis,
        RightParenthesis,
        Number,
        Operator,
        Variable,
    };

    Token(Type type, std::string content = "")
        : _type(type), _content(std::move(content)){};

    [[nodiscard]] auto get_type() const -> Type { return _type; };
    [[nodiscard]] auto get_content() const -> std::string { return _content; };

private:
    Type        _type;
    std::string _content;
};

auto tokenize_expression(std::map<char, Operator> const& operators, std::vector<char> const& variables, std::string const& expression) -> std::vector<Token>;
} // namespace mast
