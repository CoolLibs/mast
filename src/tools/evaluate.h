#pragma once

#include <cmath>
#include <string>
#include <map>
#include "../TreeNode.h"

namespace mast {

// ToDo : Do we keep that in the final project ?
auto evaluate_ast(TreeNode const& tree, std::map<char, double> variables_result) -> double;

} // namespace mast
