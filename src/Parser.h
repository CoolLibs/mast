#pragma once

#include <map>
#include <stack>
#include <string>
#include <vector>
#include "Operator.h"
#include "Tokenizer.h"
#include "TreeNode.h"

namespace mast {

using TreeNodePointer = std::shared_ptr<TreeNode>;

class Parser {
public:
    explicit Parser(std::vector<Operator> const& operators);
    auto               expression_to_ast(std::string const& expression, std::vector<char> const& variables) -> TreeNodePointer;
    [[nodiscard]] auto get_operators() const -> std::map<char, Operator> { return _operators; };

private:
    static auto create_node(std::stack<TreeNodePointer>& stack, char const& char_operator) -> TreeNodePointer;
    static void add_nodes_from_stack(std::stack<char>& operators, std::stack<TreeNodePointer>& operands);
    static void add_nodes_inside_parenthesis(std::stack<char>& operator_stack, std::stack<TreeNodePointer>& operand_stack);
    void        handle_operator_cases(std::stack<char>& operator_stack, std::stack<TreeNodePointer>& operand_stack, std::string token_content);

private:
    std::map<char, Operator> _operators;
};

} // namespace mast
