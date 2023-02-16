#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace mast {

class TreeNode {
public:
    explicit TreeNode(std::string content, std::vector<std::shared_ptr<TreeNode>> nodes = {})
        : _content(std::move(content)), _nodes(std::move(nodes))
    {}

    [[nodiscard]] auto get_content() const -> std::string { return _content; };
    [[nodiscard]] auto get_left_node() const -> TreeNode { return *_nodes[0]; };
    [[nodiscard]] auto get_right_node() const -> TreeNode { return *_nodes[1]; };

private:
    std::string                            _content;
    std::vector<std::shared_ptr<TreeNode>> _nodes;
};

using TreeNodePointer = std::shared_ptr<TreeNode>;

} // namespace mast
