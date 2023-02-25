#include "Tokenizer.h"

namespace mast {

auto is_a_valid_number(char const& c) -> bool;
auto is_a_variable(std::vector<char> const& variables, char const& c) -> bool;
auto is_an_operator(std::map<char, Operator> const& operators, char const& c) -> bool;
auto is_an_operator_or_number(std::map<char, Operator> const& operators, char const& c) -> bool;

auto tokenize_expression(std::map<char, Operator> const& operators, std::vector<char> const& variables, std::string const& expression) -> std::list<Token>
{
    std::list<Token> tokens_list{};
    for (auto it = expression.begin(); it != expression.end(); it++)
    {
        switch (*it)
        {
        case '(':
        {
            const auto fn_name_opt = tokenize_functions(tokens_list, operators, variables, it, expression.begin());
            const auto token       = fn_name_opt.empty() ? Token::Type::LeftParenthesis : Token::Type::FunctionOpening;
            tokens_list.emplace_back(token, fn_name_opt);
            break;
        }

        case ')':
        {
            const auto last_left_parenthesis     = std::find_if(tokens_list.rbegin(), tokens_list.rend(), [](Token const& token) { return token.get_type() == Token::Type::LeftParenthesis; });
            const bool has_find_left_parenthesis = last_left_parenthesis != tokens_list.rend();
            tokens_list.emplace_back(has_find_left_parenthesis ? Token::Type::RightParenthesis : Token::Type::FunctionClosing);
            break;
        }

        case ',':
            tokens_list.emplace_back(Token::Type::FunctionParameterSeparator);
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

auto tokenize_functions(std::list<Token>& tokens_list, std::map<char, Operator> const& operators, std::vector<char> const& variables, std::string::const_iterator& it, std::string::const_iterator begin) -> std::string
{
    // ToDo : Too many parameters, maybe move operators and variable into static function?
    std::string::const_iterator function_checker = std::prev(it);
    std::string                 function_name    = "";

    while (function_checker != begin && !is_an_operator_or_number(operators, *function_checker))
    {
        function_name.insert(function_name.begin(), *function_checker);

        // If the function string has an operator, it will be on top of the vector
        // ToDo : How do we handle x(x+2) ?
        if (is_a_variable(variables, *function_checker))
        {
            tokens_list.pop_back();
        }

        function_checker = std::prev(function_checker);
    }

    return function_name;
}

auto is_an_operator_or_number(std::map<char, Operator> const& operators, char const& c) -> bool
{
    return is_a_valid_number(c) || is_an_operator(operators, c) || c == '(' || c == ')' || c == ' ';
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