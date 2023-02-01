#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <mast/mast.hpp>

// Check out doctest's documentation: https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md

TEST_CASE("Get Expression Test")
{
    const auto myTree = mast::TreeBuilder{"3x+2"};
    CHECK(myTree.get_expression() == "3x+2");
}
