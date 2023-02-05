#include "TreeNode.h"

#include <utility>

namespace mast {

TreeNode::TreeNode(std::string content, std::shared_ptr<TreeNode> left, std::shared_ptr<TreeNode> right)
    : _content(std::move(content)), _left_node(left), _right_node(right)
{
}
} // namespace mast