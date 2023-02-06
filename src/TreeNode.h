#pragma once

#include <memory>
#include <string>
#include <utility>

namespace mast {

class TreeNode {
public:
    struct ChildrenNodes {
        std::shared_ptr<TreeNode> _left_node;
        std::shared_ptr<TreeNode> _right_node;
    };

public:
    explicit TreeNode(std::string content, ChildrenNodes nodes = {})
        : _content(std::move(content)), _nodes(std::move(nodes))
    {}

    [[nodiscard]] auto get_content() const -> std::string { return _content; };
    [[nodiscard]] auto get_left_node() const -> TreeNode { return *_nodes._left_node; };
    [[nodiscard]] auto get_right_node() const -> TreeNode { return *_nodes._right_node; };

private:
    std::string   _content;
    ChildrenNodes _nodes{};
};

} // namespace mast
