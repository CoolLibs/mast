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
    static auto create_node(std::stack<TreeNodePointer>& operands, char const& char_operator) -> TreeNodePointer;
    static void add_nodes_inside_parenthesis(std::stack<char>& operators, std::stack<TreeNodePointer>& operands);
    void        handle_operator_cases(std::stack<char>& operators, std::stack<TreeNodePointer>& operands, std::string token_content);
    static void add_node_with_next_token(std::stack<TreeNodePointer>& operands, std::vector<Token>::const_iterator& it, char const& wanted_operator);

private:
    std::map<char, Operator> _operators;
};

} // namespace mast
