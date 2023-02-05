#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <mast/mast.hpp>

// Check out doctest's documentation: https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md

TEST_CASE("Get Expression Test")
{
    auto operators = std::vector<mast::OperatorConcrete>{};
    //ToDo : Get a more flexible precedence
    operators.push_back(mast::OperatorConcrete{"^", true, 4});
    operators.push_back(mast::OperatorConcrete{"*", false, 3});
    operators.push_back(mast::OperatorConcrete{"/", false, 3});
    operators.push_back(mast::OperatorConcrete{"+", false, 2});
    operators.push_back(mast::OperatorConcrete{"-", false, 2});

    auto parser = mast::Parser{operators};
    std::string expression = "4 + 2";

    auto tree = parser.expression_to_ast(expression);

    //double result = mast::evaluateAST(tree);
    //std::cout << "resultat : " << result;

    //CHECK(myTree.get_expression() == "3x+2");
}
