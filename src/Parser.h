#pragma once

#include <map>
#include <stack>
#include <string>
#include <vector>
#include "OperatorConcrete.h"
#include "TreeNode.h"

namespace mast {

class Parser {
public:
    explicit Parser(std::vector<OperatorConcrete> operators);
    auto expression_to_ast(std::string expression) -> std::shared_ptr<TreeNode> ;

private:
    void add_node(std::stack<std::shared_ptr<TreeNode>>& stack, char& char_operator);

private:
    std::map<char, OperatorConcrete> _operators;
};

} // namespace mast
