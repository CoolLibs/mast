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
            if (operators.empty())
                throw std::runtime_error("Unbalanced right parentheses");
            break;

        case Token::Type::Operator:
            handle_operator_cases(operators, operands, token.get_content());
            break;

        case Token::Type::Number:
            handle_number_cases(operands, it);
            break;

        case Token::Type::Variable:
            operands.push(std::make_shared<TreeNode>(token.get_content()));
            break;

        default:
            break;
        }
    }

    add_nodes_from_stack(operators, operands);
    return operands.top();
}

auto Parser::create_node(std::stack<TreeNodePointer>& stack, char const& char_operator) -> TreeNodePointer
{
    // ToDo : Some verifications ?
    auto const right = pop_and_get_top(stack);
    auto const left  = pop_and_get_top(stack);

    return std::make_shared<TreeNode>(
        std::string(1, char_operator),
        mast::TreeNode::ChildrenNodes{left, right}
    );
}

void Parser::add_nodes_from_stack(std::stack<char>& operators, std::stack<TreeNodePointer>& operands)
{
    while (!operators.empty())
    {
        if (operators.top() == '(')
        {
            operators.pop();
            continue;
        }

        operands.push(create_node(operands, operators.top()));
        operators.pop();
    }
}

void Parser::add_nodes_inside_parenthesis(std::stack<char>& operator_stack, std::stack<TreeNodePointer>& operand_stack)
{
    while (!operator_stack.empty())
    {
        char const popped = operator_stack.top();
        operator_stack.pop();

        if (popped == '(')
            break;

        operand_stack.push(create_node(operand_stack, popped));
        break;
    }
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
            create_node(operands, o2._symbol);
        }
    }

    operators.push(token_content[0]);
}

void Parser::handle_number_cases(std::stack<TreeNodePointer>& operands, std::vector<Token>::const_iterator& it)
{
    auto const& next_token = std::next(it);
    if (next_token->get_type() == Token::Type::Variable) {
        operands.push(std::make_shared<TreeNode>(it->get_content()));
        operands.push(std::make_shared<TreeNode>(next_token->get_content()));
        operands.push(create_node(operands, '*'));
        it = next_token;
        return;
    }

    operands.push(std::make_shared<TreeNode>(it->get_content()));
}

} // namespace mast