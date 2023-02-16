#include "correct.h"

namespace mast {

void correct_token_list(std::list<Token>& tokens_list)
{
    for (auto it = tokens_list.begin(); it != tokens_list.end(); it++)
    {
        // Check the number of dots in a float
        if (it->get_type() == Token::Type::Number)
            throw_error_on_multiple_dots_number(it->get_content());

        // Add a 0 before float if it's start with a dot
        if (it->get_type() == Token::Type::Number && it->get_content()[0] == '.')
            it->get_content().insert(1, "0");

        // Add * in implicits multiplications
        handle_implicit_multiplication(tokens_list, it);
    }
}

void throw_error_on_multiple_dots_number(std::string token_content)
{
    // ToDo : Better exception
    if (std::count(token_content.begin(), token_content.end(), '.') > 1)
        throw std::runtime_error("Error Expression : Multiple dots");
};

void handle_implicit_multiplication(std::list<Token>& tokens_list, std::list<Token>::const_iterator current)
{
    auto next_it = std::next(current);

    // ToDo : refacto "_impl" lambda !!!!! "implicit_mult_between(var,num)"

    // x(x+2)
    if (current->get_type() == Token::Type::Variable)
        if (next_it->get_type() == Token::Type::LeftParenthesis)
            tokens_list.emplace(next_it, Token::Type::Operator, "*");

    // 4.34x AND 4.43(x+1)
    if (current->get_type() == Token::Type::Number)
        if (next_it->get_type() == Token::Type::Variable || next_it->get_type() == Token::Type::LeftParenthesis)
            tokens_list.emplace(next_it, Token::Type::Operator, "*");

    // (x+1)x AND (x+1)4.3
    if (current->get_type() == Token::Type::RightParenthesis)
        if (next_it->get_type() == Token::Type::Variable || next_it->get_type() == Token::Type::Number)
            tokens_list.emplace(next_it, Token::Type::Operator, "*");

}

} // namespace mast
