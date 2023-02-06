#pragma once

#include <map>
#include <stack>
#include <string>
#include <vector>
#include "Operator.h"
#include "TreeNode.h"

namespace mast {

class Parser {
public:
    explicit Parser(std::vector<Operator> const& operators);
    auto expression_to_ast(std::string const& expression) -> std::shared_ptr<TreeNode>;

private:
    static void add_node(std::stack<std::shared_ptr<TreeNode>>& stack, char const& char_operator);
    static void add_nodes_from_stack(std::stack<char>& operator_stack, std::stack<std::shared_ptr<TreeNode>>& operand_stack);
    static void add_nodes_inside_parenthesis(std::stack<char>& operator_stack, std::stack<std::shared_ptr<TreeNode>>& operand_stack, char& popped);
    void handle_operator_cases(std::stack<char>& operand_stack, std::stack<std::shared_ptr<TreeNode>>& operator_stack, char c);

private:
    std::map<char, Operator> _operators;
};

} // namespace mast
