#pragma once

#include <algorithm>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "Operator.h"

namespace mast {

class Token {
public:
    enum class Type {
        LeftParenthesis,
        RightParenthesis,
        Number,
        Operator,
        Variable,
        FunctionOpening,
        FunctionClosing,
    };

    explicit Token(Type type, std::string content = "")
        : _type(type), _content(std::move(content)){};

    [[nodiscard]] auto get_type() const -> Type { return _type; };
    [[nodiscard]] auto get_content() const -> std::string { return _content; };

private:
    Type        _type;
    std::string _content;
};

auto tokenize_expression(std::map<char, Operator> const& operators, std::vector<char> const& variables, std::string const& expression) -> std::list<Token>;
auto tokenize_numbers(std::string::const_iterator& it, std::string::const_iterator end) -> std::string;
auto tokenize_functions(std::list<Token>& tokens_list, std::map<char, Operator> const& operators, std::vector<char> const& variables, std::string::const_iterator& it, std::string::const_iterator begin) -> std::string;

} // namespace mast
