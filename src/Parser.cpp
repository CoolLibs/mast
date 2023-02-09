#include "Parser.h"
#include <memory>
#include <stdexcept>

namespace mast {

Parser::Parser(std::vector<Operator> const& operators)
{
    for (const auto& o : operators)
        // ToDo : We will stock string instead of char so we'll get rid of [0]
        _operators.insert({o._symbol[0], o});
}

auto Parser::expression_to_ast(std::string const& expression, std::vector<char> const& variables) -> std::shared_ptr<TreeNode>
{
    // ToDo : We will stock string instead of char
    std::stack<char>                      operator_stack{};
    std::stack<std::shared_ptr<TreeNode>> operand_stack{};

    std::string::const_iterator it;
    for (it = expression.begin(); it != expression.end(); it++)
    {
        char const c      = *it;
        char       popped = 0;

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
                // ToDo: handle_function_cases();
                handle_number_cases(operand_stack, it, variables);
            break;
        }
    }

    add_nodes_from_stack(operator_stack, operand_stack);

    return operand_stack.top();
}

auto Parser::create_node(std::stack<std::shared_ptr<TreeNode>>& stack, char const& char_operator) -> std::shared_ptr<TreeNode>
{
    // ToDo : Some verifications ?
    std::shared_ptr<TreeNode> const right = stack.top();
    stack.pop();

    std::shared_ptr<TreeNode> const left = stack.top();
    stack.pop();

    return std::make_shared<TreeNode>(
        std::string(1, char_operator),
        mast::TreeNode::ChildrenNodes{left, right}
    );
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

        operand_stack.push(create_node(operand_stack, operator_stack.top()));
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

        operand_stack.push(create_node(operand_stack, popped));
        break;
    }
}

void Parser::handle_number_cases(std::stack<std::shared_ptr<TreeNode>>& operand_stack, std::string::const_iterator& it, std::vector<char> variables)
{
    // ToDo : Scientific notation
    auto operand           = std::string(1, *it);
    auto is_a_valid_number = [](char const& c) {
        return std::isdigit(c) || c == '.';
    };
    auto is_a_variable = [&](char const& c) {
        return std::count(variables.begin(), variables.end(), c);
    };

    if (!is_a_valid_number(*it))
    {
        if (!is_a_variable(*it))
            throw std::runtime_error("Not a valid variable name");

        operand_stack.push(std::make_shared<TreeNode>(operand));
        return;
    }

    bool operand_is_a_float = false;
    if (*it == '.')
    {
        operand_is_a_float = true;
        operand.insert(0, std::string(1, '0'));
    }

    std::string::const_iterator next_character = std::next(it);
    while (*next_character != 0 && (is_a_valid_number(*next_character) || is_a_variable(*next_character)))
    {
        if (*next_character == '.')
        {
            if (operand_is_a_float)
                throw std::runtime_error("Multiple dots");
            operand_is_a_float = true;
        }

        if (is_a_variable(*next_character))
        {
            operand_stack.push(std::make_shared<TreeNode>(operand));
            operand_stack.push(std::make_shared<TreeNode>(std::string(1, *next_character)));
            operand_stack.push(create_node(operand_stack, '*'));
            it = next_character;
            return;
        }

        operand.append(std::string(1, *next_character));
        next_character = std::next(next_character);
        it             = std::next(it);
    }

    operand_stack.push(std::make_shared<TreeNode>(operand));
}

void Parser::handle_operator_cases(std::stack<char>& operator_stack, std::stack<std::shared_ptr<TreeNode>>& operand_stack, char c)
{
    Operator const o1 = _operators.at(c);

    while (!operator_stack.empty() && _operators.contains(operator_stack.top()))
    {
        Operator const& o2 = _operators.at(operator_stack.top());

        if ((!o1._right_associative && o1._precedence == o2._precedence)
            || o1._precedence > o2._precedence)
        {
            operator_stack.pop();
            create_node(operand_stack, o2._symbol[0]);
        }

        else
            continue;
    }

    operator_stack.push(c);
}

} // namespace mast