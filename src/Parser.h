#pragma once

#include <map>
#include <stack>
#include <string>
#include <vector>
#include "Operator.h"
#include "TreeNode.h"
#include "Tokenizer.h"

namespace mast {

class Parser {
public:
    explicit Parser(std::vector<Operator> const& operators);
    auto expression_to_ast(std::string const& expression, std::vector<char> const& variables) -> std::shared_ptr<TreeNode>;
    [[nodiscard]] auto get_operators() const -> std::map<char, Operator> { return _operators; };
private:
    static auto create_node(std::stack<std::shared_ptr<TreeNode>>& stack, char const& char_operator) -> std::shared_ptr<TreeNode>;
    static void add_nodes_from_stack(std::stack<char>& operator_stack, std::stack<std::shared_ptr<TreeNode>>& operand_stack);
    static void add_nodes_inside_parenthesis(std::stack<char>& operator_stack, std::stack<std::shared_ptr<TreeNode>>& operand_stack, char& popped);

    // ToDo: Refacto these parameters
    static void handle_number_cases(std::stack<std::shared_ptr<TreeNode>>& operand_stack, const std::vector<char>& variables, std::string const& token_content);
    void handle_operator_cases(std::stack<char>& operator_stack, std::stack<std::shared_ptr<TreeNode>>& operand_stack, std::string token_content);

private:
    std::map<char, Operator> _operators;
};

} // namespace mast
