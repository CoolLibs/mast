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
    std::stack<char>                      operator_stack{};
    std::stack<std::shared_ptr<TreeNode>> operand_stack{};

    auto const token_list = mast::tokenize_expression(_operators, variables, expression);

    for (auto const& token : token_list)
    {
        char popped = 0;

        switch (token.get_type())
        {
        case Token::Type::LeftParenthesis:
            operator_stack.push('(');
            break;

        case Token::Type::RightParenthesis:
            add_nodes_inside_parenthesis(operator_stack, operand_stack, popped);

            if (operator_stack.empty())
                throw std::runtime_error("Unbalanced right parentheses");
            break;

        case Token::Type::Operator:
            handle_operator_cases(operator_stack, operand_stack, token.get_content());
            break;

        default:
            // ToDo: handle_function_cases();
            handle_number_cases(operand_stack, variables, token.get_content());
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

void Parser::handle_number_cases(std::stack<std::shared_ptr<TreeNode>>& operand_stack, const std::vector<char>& variables, std::string const& token_content)
{
    operand_stack.push(std::make_shared<TreeNode>(token_content));
}

void Parser::handle_operator_cases(std::stack<char>& operator_stack, std::stack<std::shared_ptr<TreeNode>>& operand_stack, std::string token_content)
{
    Operator const o1 = _operators.at(token_content[0]);

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

    operator_stack.push(token_content[0]);
}

} // namespace mast