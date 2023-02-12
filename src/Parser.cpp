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

void Parser::correct_token_list(std::vector<Token>& tokens_list)
{
    for (auto it = tokens_list.begin(); it != tokens_list.end(); it++)
    {
        /****** Add * in implicit multiplication ******/
        if (it->get_type() == Token::Type::Number)
        {
            // Before variable
            if (std::next(it)->get_type() == Token::Type::Variable)
                it = tokens_list.emplace(it + 1, Token::Type::Operator, "*");

            // Before ()
            if (std::next(it)->get_type() == Token::Type::LeftParenthesis)
                it = tokens_list.emplace(it + 1, Token::Type::Operator, "*");
        }
    }
}

auto Parser::expression_to_ast(std::string const& expression, std::vector<char> const& variables) -> std::shared_ptr<TreeNode>
{
    auto                        token_list = mast::tokenize_expression(_operators, variables, expression);
    std::stack<TreeNodePointer> operands{};
    std::stack<char>            operators{};

    correct_token_list(token_list);

    for (auto it = token_list.begin(); it != token_list.end(); it++)
    {
        std::string const& token_content = it->get_content();
        switch (it->get_type())
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
            operands.push(std::make_shared<TreeNode>(token_content));
            break;

        case Token::Type::Variable:
            operands.push(std::make_shared<TreeNode>(token_content));
            break;

        default:
            break;
        }
    }

    // Create nodes from stacks
    while (!operators.empty() && _operators.contains(operators.top()))
        add_node(operands, pop_and_get_top(operators));

    return operands.top();
}

void Parser::add_node(std::stack<TreeNodePointer>& operands, char const& char_operator)
{
    // ToDo : Should I do verifications ?
    auto const right = pop_and_get_top(operands);
    auto const left  = pop_and_get_top(operands);

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
        current_operator = pop_and_get_top(operators);
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

void Parser::create_and_add_node_with_next_token_content(std::stack<TreeNodePointer>& operands, std::vector<Token>::const_iterator& it, char const& wanted_operator)
{
    auto const& next_token = std::next(it);
    operands.push(std::make_shared<TreeNode>(it->get_content()));
    operands.push(std::make_shared<TreeNode>(next_token->get_content()));
    add_node(operands, wanted_operator);
    it = next_token;
}

} // namespace mast