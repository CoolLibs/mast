#pragma once

#include <cmath>
#include "TreeNode.h"

namespace mast {
double evaluateAST(TreeNode tree)
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
        return tree.get_content()[0];
        break;
    }
}
} // namespace mast
