#include "TreeBuilder.h"

namespace mast {

auto TreeBuilder::create_tree() const -> TreeNode
{
    // ToDo: Create a tree !
    return TreeNode{Token{Token::Type::Number, "2"}};
}

} // namespace mast