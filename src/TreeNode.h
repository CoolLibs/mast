#pragma once

#include <string>
#include "Token.h"

namespace mast {

class TreeNode {
public:
    explicit TreeNode(Token, TreeNode* left = {}, TreeNode* right = {});

public:
    auto get_content() -> Token { return _content; };
    auto get_left_node() -> TreeNode { return *_left_node; };
    auto get_right_node() -> TreeNode { return *_right_node; };

private:
    Token _content;
    TreeNode* _left_node;
    TreeNode* _right_node;
};

} // namespace mast
