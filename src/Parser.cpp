#include "Parser.h"
#include <iostream>
#include <memory>
#include <stdexcept>

namespace mast {

Parser::Parser(std::vector<OperatorConcrete> operators)
{
    for (auto o : operators)
    {
        _operators.insert({o.get_symbol()[0], o});
    }
}

auto Parser::expression_to_ast(std::string expression) -> std::shared_ptr<TreeNode>
{
    std::stack<char>                      operator_stack{};
    std::stack<std::shared_ptr<TreeNode>> operand_stack{};

    std::string::const_iterator it;
    for (it = expression.begin(); it != expression.end(); it++)
    {
        char c = *it;
        char popped;

        switch (c)
        {
        case ' ':
            break;
        case '(':
            operator_stack.push('(');
            break;
        case ')':
            while (!operator_stack.empty())
            {
                popped = operator_stack.top();
                operator_stack.pop();

                if (popped == '(')
                {
                    break;
                }
                else
                {
                    add_node(operand_stack, popped);
                    break;
                }
            }
            // ToDo: Verif is useless
            if (operator_stack.empty())
            {
                // ToDo : better exception
                throw std::runtime_error("Unbalanced right parentheses");
            }
            break;
        default:
            if (_operators.count(c))
            {
                OperatorConcrete  o1 = _operators.at(c);
                OperatorConcrete* o2 = nullptr;

                while (!operator_stack.empty())
                {
                    o2 = &_operators.at(operator_stack.top());
                    if ((!o1.is_right_associative() && o1.compare_precedence(o2) == 0) || o1.compare_precedence(o2) < 0)
                    {
                        operator_stack.pop();
                        add_node(operand_stack, o2->get_symbol()[0]);
                    }
                    else
                    {
                        continue;
                    }
                }
                operator_stack.push(c);
            }
            else
            {
                operand_stack.push(std::make_shared<TreeNode>(std::string(1, c), nullptr, nullptr));
            }
            break;
        }
    }
    while (!operator_stack.empty())
    {
        add_node(operand_stack, operator_stack.top());

        operator_stack.pop();
    }

    return operand_stack.top();
}

void Parser::add_node(std::stack<std::shared_ptr<TreeNode>>& stack, char& char_operator)
{
    std::shared_ptr<TreeNode> right = stack.top();
    stack.pop();

    std::shared_ptr<TreeNode> left = stack.top();
    stack.pop();

    stack.push(std::make_shared<TreeNode>(std::string(1, char_operator), left, right));
}
} // namespace mast