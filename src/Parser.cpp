#include "Parser.h"
#include <memory>
#include <stdexcept>

namespace mast {

Parser::Parser(std::vector<Operator> const& operators)
{
    for (const auto& o : operators)
        // ToDo : We will stock string instead of char so we'll get rid of [0]
        _operators.insert({o.get_symbol()[0], o});
}

auto Parser::expression_to_ast(std::string const& expression) -> std::shared_ptr<TreeNode>
{
    // ToDo : We will stock string instead of char
    std::stack<char>                      operator_stack{};
    std::stack<std::shared_ptr<TreeNode>> operand_stack{};

    for (auto const& c : expression)
    {
        char popped = 0;

        switch (c)
        {
        case ' ':
            break;

        case '(':
            operator_stack.push('(');
            break;

        case ')':
            add_nodes_inside_parenthesis(operator_stack, operand_stack, popped);

            if (operator_stack.empty())
                throw std::runtime_error("Unbalanced right parentheses");
            break;

        default:
            if (_operators.contains(c))
                handle_operator_cases(operator_stack, operand_stack, c);
            else
                operand_stack.push(std::make_shared<TreeNode>(std::string(1, c)));
            break;
        }
    }

    add_nodes_from_stack(operator_stack, operand_stack);
    return operand_stack.top();
}

void Parser::add_node(std::stack<std::shared_ptr<TreeNode>>& stack, char const& char_operator)
{
    // ToDo : Some verifications ?
    std::shared_ptr<TreeNode> const right = stack.top();
    stack.pop();

    std::shared_ptr<TreeNode> const left = stack.top();
    stack.pop();

    stack.push(std::make_shared<TreeNode>(
        std::string(1, char_operator),
        mast::TreeNode::ChildrenNodes{left, right}
    ));
}

void Parser::add_nodes_from_stack(std::stack<char>& operator_stack, std::stack<std::shared_ptr<TreeNode>>& operand_stack)
{
    while (!operator_stack.empty())
    {
        // ToDo : This verification was not in the java example ?
        if (operator_stack.top() == '(')
        {
            operator_stack.pop();
            continue;
        }

        add_node(operand_stack, operator_stack.top());
        operator_stack.pop();
    }
}

void Parser::add_nodes_inside_parenthesis(std::stack<char>& operator_stack, std::stack<std::shared_ptr<TreeNode>>& operand_stack, char& popped)
{
    while (!operator_stack.empty())
    {
        popped = operator_stack.top();
        operator_stack.pop();

        if (popped == '(')
            break;

        add_node(operand_stack, popped);
        break;
    }
}

void Parser::handle_operator_cases(std::stack<char>& operator_stack, std::stack<std::shared_ptr<TreeNode>>& operand_stack, char c)
{
    Operator const o1 = _operators.at(c);
    Operator*      o2 = nullptr;

    while (!operator_stack.empty() && _operators.contains(operator_stack.top()))
    {
        o2 = &_operators.at(operator_stack.top());

        if ((!o1.is_right_associative() && o1.get_precedence() == o2->get_precedence())
            || o1.get_precedence() > o2->get_precedence())
        {
            operator_stack.pop();
            add_node(operand_stack, o2->get_symbol()[0]);
        }

        else
            continue;
    }

    operator_stack.push(c);
}

} // namespace mast