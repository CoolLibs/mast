#include "TreeNode.h"

namespace mast {

TreeNode::TreeNode(Token content, TreeNode* left, TreeNode* right)
    : _content(content), _left_node(left), _right_node(right)
{}
} // namespace mast