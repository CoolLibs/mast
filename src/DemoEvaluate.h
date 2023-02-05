#pragma once

#include <cmath>
#include <string>
#include "TreeNode.h"

namespace mast {
auto evaluateAST(TreeNode const& tree) -> double
{
    switch (tree.get_content()[0])
    {
    case '^':
        return std::pow(evaluateAST(tree.get_left_node()), evaluateAST(tree.get_right_node()));
        break;

    case '*':
        return evaluateAST(tree.get_left_node()) * evaluateAST(tree.get_right_node());
        break;

    case '/':
        return evaluateAST(tree.get_left_node()) / evaluateAST(tree.get_right_node());
        break;

    case '+':
        return evaluateAST(tree.get_left_node()) + evaluateAST(tree.get_right_node());
        break;

    case '-':
        return evaluateAST(tree.get_left_node()) - evaluateAST(tree.get_right_node());
        break;

    default:
        return std::stoi(tree.get_content());
        break;
    }
}
} // namespace mast
