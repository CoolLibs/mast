#include "Parser.h"
#include <memory>
#include <stdexcept>
#include "tools/expressions/correct.h"
#include "tools/utils.h"

namespace mast {

Parser::Parser(std::vector<Operator> const& operators)
{
    for (const auto& o : operators)
        _operators.insert({o._symbol, o});
}

auto Parser::expression_to_ast(std::string const& expression, std::vector<char> const& variables) -> std::shared_ptr<TreeNode>
{
    auto                        token_list = mast::tokenize_expression(_operators, variables, expression);
    std::stack<TreeNodePointer> operands{};
    std::stack<char>            operators{};

    correct_token_list(token_list);

    for (auto const& token : token_list)
    {
        std::string const& token_content = token.get_content();
        switch (token.get_type())
        {
        case Token::Type::LeftParenthesis:
            operators.push('(');
            break;

        case Token::Type::RightParenthesis:
            add_nodes_from_parenthesis_content(operators, operands);
            break;

        case Token::Type::Operator:
            add_nodes_from_stacks(operators, operands, token_content);
            operators.push(token_content[0]);
            break;

        case Token::Type::Number:
        case Token::Type::Variable:
            operands.push(std::make_shared<TreeNode>(token_content));
            break;

        default:
            break;
        }
    }

    // Create nodes from stacks
    while (!operators.empty() && _operators.contains(operators.top()))
        add_node(operands, get_top_and_pop(operators));

    return operands.top();
}

void Parser::add_node(std::stack<TreeNodePointer>& operands, char const& char_operator)
{
    // ToDo : Should I do verifications ?
    auto const right = get_top_and_pop(operands);
    auto const left  = get_top_and_pop(operands);

    operands.push(std::make_shared<TreeNode>(
        std::string(1, char_operator),
        mast::TreeNode::ChildrenNodes{left, right}
    ));
}

void Parser::add_nodes_from_parenthesis_content(std::stack<char>& operators, std::stack<TreeNodePointer>& operands)
{
    char current_operator = 0;
    while (!operators.empty())
    {
        current_operator = get_top_and_pop(operators);
        if (current_operator == '(')
            break;

        add_node(operands, current_operator);
    }

    if (operators.empty() && current_operator != '(')
        throw std::runtime_error("Unbalanced right parentheses");
}

void Parser::add_nodes_from_stacks(std::stack<char>& operators, std::stack<TreeNodePointer>& operands, std::string token_content)
{
    Operator const current_operator = _operators.at(token_content[0]);
    while (!operators.empty() && _operators.contains(operators.top()))
    {
        Operator const last_operator = _operators.at(operators.top());
        if ((!current_operator._right_associative && current_operator._precedence == last_operator._precedence)
            || (current_operator._precedence < last_operator._precedence))
        {
            operators.pop();
            add_node(operands, last_operator._symbol);
        }

        else
            break;
    }
}

} // namespace mast