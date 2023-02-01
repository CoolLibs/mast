#include "Parser.h"

namespace mast {

Parser::Parser(std::vector<OperatorConcrete> operators)
{
    for (auto o : operators)
    {
        _operators.insert({o.get_symbol()[0], o});
    }
}

auto Parser::expression_to_ast(std::string expression) -> TreeNode
{
    std::stack<char>     operator_stack{};
    std::stack<TreeNode> operand_stack{};

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
            if (operator_stack.empty())
            {
                // ToDo : "Unbalanced right parentheses" exception
                throw std::exception();
            }
            break;
        default:
            if (_operators.count(c))
            {
                OperatorConcrete  o1 = _operators.at(c);
                OperatorConcrete* o2 = nullptr;
                while (!operator_stack.empty() && _operators.count(operator_stack.top()))
                {
                    o2 = &_operators.at(operator_stack.top());
                    if ((!o1.is_right_associative() && o1.get_precedence() == o2->get_precedence()) || o2->get_precedence() > o1.get_precedence())
                    {
                        operator_stack.pop();
                        add_node(operand_stack, o2->get_symbol()[0]);
                    }
                    else
                    {
                        break;
                    }
                }
                operator_stack.push(c);
            }
            else
            {
                operand_stack.push(TreeNode{std::string(1, c), nullptr, nullptr});
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

void Parser::add_node(std::stack<TreeNode>& stack, char char_operator)
{
    TreeNode right = stack.top();
    stack.pop();

    TreeNode left = stack.top();
    stack.pop();

    stack.push(TreeNode{std::string(1, char_operator), &left, &right});
}
} // namespace mast