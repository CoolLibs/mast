#pragma once

#include <memory>
#include <string>

namespace mast {

class TreeNode {
public:
    explicit TreeNode(std::string, std::shared_ptr<TreeNode> left = {}, std::shared_ptr<TreeNode> right = {});

public:
    auto get_content() -> std::string { return _content; };
    auto get_left_node() -> TreeNode { return *_left_node; };
    auto get_right_node() -> TreeNode { return *_right_node; };

private:
    std::string               _content;
    std::shared_ptr<TreeNode> _left_node;
    std::shared_ptr<TreeNode> _right_node;
};

} // namespace mast
