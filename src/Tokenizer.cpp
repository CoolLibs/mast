#include "Tokenizer.h"

namespace mast {

auto is_a_valid_number(char const& c) -> bool;
auto is_a_variable(std::vector<char> const& variables, char const& c) -> bool;
auto is_an_operator(std::map<char, Operator> const& operators, char const& c) -> bool;

auto tokenize_expression(std::map<char, Operator> const& operators, std::vector<char> const& variables, std::string const& expression) -> std::list<Token>
{
    std::list<Token> tokens_list{};
    for (auto it = expression.begin(); it != expression.end(); it++)
    {
        switch (*it)
        {
        case ' ':
            break;

        case '(':
            tokens_list.emplace_back(Token::Type::LeftParenthesis);
            break;

        case ')':
            tokens_list.emplace_back(Token::Type::RightParenthesis);
            break;

        default:
            if (is_an_operator(operators, *it))
                tokens_list.emplace_back(Token::Type::Operator, std::string(1, *it));

            if (is_a_valid_number(*it))
                tokens_list.emplace_back(Token::Type::Number, tokenize_numbers(it, expression.end()));

            if (is_a_variable(variables, *it))
                tokens_list.emplace_back(Token::Type::Variable, std::string(1, *it));
        }
    }

    return tokens_list;
}

auto tokenize_numbers(std::string::const_iterator& it, std::string::const_iterator end) -> std::string
{
    std::string operand = std::string(1, *it);

    std::string::const_iterator next_character = std::next(it);
    while (next_character != end && (is_a_valid_number(*next_character)))
    {
        operand.append(std::string(1, *next_character));
        next_character = std::next(next_character);
        it             = std::next(it);
    }

    return operand;
}

auto is_a_valid_number(char const& c) -> bool
{
    return std::isdigit(c) || c == '.';
};

auto is_a_variable(std::vector<char> const& variables, char const& c) -> bool
{
    return std::count(variables.begin(), variables.end(), c);
};

auto is_an_operator(std::map<char, Operator> const& operators, char const& c) -> bool
{
    return operators.contains(c);
};

} // namespace mast