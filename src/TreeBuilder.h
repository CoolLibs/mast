#pragma once

#include <string>
#include <utility>
#include "./TreeNode.h"

namespace mast {
class TreeBuilder {
public:
    explicit TreeBuilder(std::string expression)
        : _expression(std::move(expression)) {}

    [[nodiscard]] auto get_expression() const -> std::string { return _expression; };

    // ToDo Variables

    [[nodiscard]] auto create_tree() const -> TreeNode;

private:
    std::string _expression;
};

} // namespace mast
