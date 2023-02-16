#include "correct.h"
#include <stdexcept>

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
        handle_implicit_multiplications(tokens_list, it);
    }
}

void throw_error_on_multiple_dots_number(std::string token_content)
{
    // ToDo : Better exception
    if (std::count(token_content.begin(), token_content.end(), '.') > 1)
        throw std::runtime_error("Error Expression : Multiple dots");
};

void handle_implicit_multiplications(std::list<Token>& tokens_list, std::list<Token>::const_iterator current)
{
    auto next_it = std::next(current);

    const auto handle_implicit_multiplication_between = [&](Token::Type first_type, std::vector<Token::Type> other_types) {
        if (current->get_type() == first_type
            && std::find(other_types.begin(), other_types.end(), next_it->get_type()) != other_types.end())
            tokens_list.emplace(next_it, Token::Type::Operator, "*");
    };

    handle_implicit_multiplication_between(Token::Type::Variable, {Token::Type::LeftParenthesis});
    handle_implicit_multiplication_between(Token::Type::Number, {Token::Type::Variable, Token::Type::LeftParenthesis});
    handle_implicit_multiplication_between(Token::Type::RightParenthesis, {Token::Type::Number});
}

} // namespace mast
