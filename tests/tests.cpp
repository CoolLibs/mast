#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <map>
#include <mast/mast.hpp>

// Check out doctest's documentation: https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md

TEST_CASE("Get Expression Test")
{
    auto operators = std::vector<mast::Operator>{};
    // ToDo : Get a more flexible precedence
    // ToDo : right associative in default parameter
    operators.push_back({'^', 4, true});
    operators.push_back({'*', 3});
    operators.push_back({'/', 3});
    operators.push_back({'+', 2});
    operators.push_back({'-', 2});

    auto variables = std::vector<char>{'x'};
    auto parser    = mast::Parser{operators};

    std::string const expression = "(4x + 23.5)*(3^2) / x";
    auto const        tree       = parser.expression_to_ast(expression, variables);
    double const      result     = mast::evaluate_ast(*tree, std::map<char, double>{{'x', 5.}});
    std::cout << "resultat : " << result;
    CHECK(result == 78.3);
}
