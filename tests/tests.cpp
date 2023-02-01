#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <mast/mast.hpp>

// Check out doctest's documentation: https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md

TEST_CASE("Get Expression Test")
{
    auto operators = std::vector<mast::OperatorConcrete>{};
    operators.push_back(mast::OperatorConcrete{"^", true, 4});

    auto parser = mast::Parser{operators};
    std::string expression = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";

    mast::TreeNode tree = parser.expression_to_ast(expression);
    double result = mast::evaluateAST(tree);
    std::cout << "resultat : " << result;

    //CHECK(myTree.get_expression() == "3x+2");
}
