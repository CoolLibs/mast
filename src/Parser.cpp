#include "Parser.h"
#include <memory>
#include <stdexcept>
#include "tools/utils.h"

namespace mast {

Parser::Parser(std::vector<Operator> const& operators)
{
    for (const auto& o : operators)
        _operators.insert({o._symbol, o});
}

auto Parser::expression_to_ast(std::string const& expression, std::vector<char> const& variables) -> std::shared_ptr<TreeNode>
{
    auto const                  token_list = mast::tokenize_expression(_operators, variables, expression);
    std::stack<TreeNodePointer> operands{};
    std::stack<char>            operators{};

    std::vector<Token>::const_iterator it;
    for (it = token_list.begin(); it != token_list.end(); it++)
    {
        Token const& token = *it;
        switch (token.get_type())
        {
        case Token::Type::LeftParenthesis:
            operators.push('(');
            break;

        case Token::Type::RightParenthesis:
            add_nodes_inside_parenthesis(operators, operands);
            break;

        case Token::Type::Operator:
        {
            Operator const fetched_operator = _operators.at(token.get_content()[0]);

            // While operator stack doesn't contain any operator (can still have parenthesis)
            while (!operators.empty() && _operators.contains(operators.top()))
            {
                Operator const last_operator = _operators.at(operators.top());

                if ((!fetched_operator._right_associative && fetched_operator._precedence == last_operator._precedence) || (fetched_operator._precedence < last_operator._precedence))
                {
                    operators.pop();
                    operands.push(create_node(operands, last_operator._symbol));
                }

                else
                    break;
            }

            // We push in the operator stack the current operator
            operators.push(token.get_content()[0]);
            // handle_operator_cases(operators, operands, token.get_content());
            break;
        }

        case Token::Type::Number:
            // Handle "4x" case
            if (std::next(it)->get_type() == Token::Type::Variable)
            {
                add_node_with_next_token(operands, it, '*');
                break;
            }
            operands.push(std::make_shared<TreeNode>(token.get_content()));
            break;

        case Token::Type::Variable:
            operands.push(std::make_shared<TreeNode>(token.get_content()));
            break;

        default:
            break;
        }
    }

    while (!operators.empty() && _operators.contains(operators.top()))
        operands.push(create_node(operands, pop_and_get_top(operators)));

    return operands.top();
}

auto Parser::create_node(std::stack<TreeNodePointer>& operands, char const& char_operator) -> TreeNodePointer
{
    // ToDo : Some verifications ?
    auto const right = pop_and_get_top(operands);
    auto const left  = pop_and_get_top(operands);

    return std::make_shared<TreeNode>(
        std::string(1, char_operator),
        mast::TreeNode::ChildrenNodes{left, right}
    );
}

void Parser::add_nodes_inside_parenthesis(std::stack<char>& operators, std::stack<TreeNodePointer>& operands)
{
    char current_operator = 0;
    while (!operators.empty())
    {
        current_operator = pop_and_get_top(operators);

        if (current_operator == '(')
            break;

        operands.push(create_node(operands, current_operator));
    }

    if (operators.empty() && current_operator != '(')
        throw std::runtime_error("Unbalanced right parentheses");
}

void Parser::handle_operator_cases(std::stack<char>& operators, std::stack<TreeNodePointer>& operands, std::string token_content)
{
    // Operator has a char
    Operator const o1 = _operators.at(token_content[0]);

    while (!operators.empty() && _operators.contains(operators.top()))
    {
        Operator const& o2 = _operators.at(operators.top());
        if ((!o1._right_associative && o1._precedence == o2._precedence) || o1._precedence > o2._precedence)
        {
            operators.pop();
            operands.push(create_node(operands, o2._symbol));
        }

        else
            break;
    }

    operators.push(token_content[0]);
}

void Parser::add_node_with_next_token(std::stack<TreeNodePointer>& operands, std::vector<Token>::const_iterator& it, char const& wanted_operator)
{
    auto const& next_token = std::next(it);
    operands.push(std::make_shared<TreeNode>(it->get_content()));
    operands.push(std::make_shared<TreeNode>(next_token->get_content()));
    operands.push(create_node(operands, wanted_operator));
    it = next_token;
}

} // namespace mast