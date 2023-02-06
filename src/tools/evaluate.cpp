#include "evaluate.h"

namespace mast {

auto evaluateAST(TreeNode const& tree) -> double
{
    // ToDo : We will stock string instead of char so we'll get rid of [0]
    switch (tree.get_content()[0])
    {
    case '^':
        return std::pow(evaluateAST(tree.get_left_node()), evaluateAST(tree.get_right_node()));

    case '*':
        return evaluateAST(tree.get_left_node()) * evaluateAST(tree.get_right_node());

    case '/':
        return evaluateAST(tree.get_left_node()) / evaluateAST(tree.get_right_node());

    case '+':
        return evaluateAST(tree.get_left_node()) + evaluateAST(tree.get_right_node());

    case '-':
        return evaluateAST(tree.get_left_node()) - evaluateAST(tree.get_right_node());

    default:
        return std::stoi(tree.get_content());
    }
}

} // namespace mast
