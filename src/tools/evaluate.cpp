#include "evaluate.h"

namespace mast {

auto evaluate_ast(TreeNode const& tree, std::map<char, double> variables_result) -> double
{
    // ToDo : We will stock string instead of char so we'll get rid of [0]
    switch (tree.get_content()[0])
    {
    case '^':
        return std::pow(evaluate_ast(tree.get_left_node(), variables_result), evaluate_ast(tree.get_right_node(), variables_result));

    case '*':
        return evaluate_ast(tree.get_left_node(), variables_result) * evaluate_ast(tree.get_right_node(), variables_result);

    case '/':
        return evaluate_ast(tree.get_left_node(), variables_result) / evaluate_ast(tree.get_right_node(), variables_result);

    case '+':
        return evaluate_ast(tree.get_left_node(), variables_result) + evaluate_ast(tree.get_right_node(), variables_result);

    case '-':
        return evaluate_ast(tree.get_left_node(), variables_result) - evaluate_ast(tree.get_right_node(), variables_result);

    default:

        if (variables_result.contains(tree.get_content()[0]))
            return variables_result.at(tree.get_content()[0]);
        else
            return std::stof(tree.get_content());
    }
}

} // namespace mast
