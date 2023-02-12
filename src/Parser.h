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
    auto expression_to_ast(std::string const& expression, std::vector<char> const& variables) -> TreeNodePointer;

private:
    static void correct_token_list(std::vector<Token>& tokens_list);
    static void add_node(std::stack<TreeNodePointer>& operands, char const& char_operator);
    static void add_nodes_from_parenthesis_content(std::stack<char>& operators, std::stack<TreeNodePointer>& operands);
    static void create_and_add_node_with_next_token_content(std::stack<TreeNodePointer>& operands, std::vector<Token>::const_iterator& it, char const& wanted_operator);
    void        add_nodes_from_stacks(std::stack<char>& operators, std::stack<TreeNodePointer>& operands, std::string token_content);

private:
    std::map<char, Operator> _operators;
};

} // namespace mast
