#pragma once

#include <string>

namespace mast {

class TreeNode {
public:
    explicit TreeNode(std::string, TreeNode* left = {}, TreeNode* right = {});

public:
    auto get_content() -> std::string { return _content; };
    auto get_left_node() -> TreeNode { return *_left_node; };
    auto get_right_node() -> TreeNode { return *_right_node; };

private:
    std::string _content;
    TreeNode*   _left_node;
    TreeNode*   _right_node;
};

} // namespace mast
