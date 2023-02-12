#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <map>
#include <mast/mast.hpp>

// Check out doctest's documentation: https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md

TEST_CASE("Get Expression Test")
{
    auto operators = std::vector<mast::Operator>{};
    // ToDo : Get a more flexible precedence
    operators.push_back({'^', 4, true});
    operators.push_back({'*', 3});
    operators.push_back({'/', 3});
    operators.push_back({'+', 2});
    operators.push_back({'-', 2});

    auto variables = std::vector<char>{'x'};
    auto parser    = mast::Parser{operators};

    std::string const expression = "(4x + 23.5)*(3^2) / (1 + x^2)";
    double const      result     = mast::evaluate_ast(
        *parser.expression_to_ast(expression, variables),
        std::map<char, double>{{'x', 5.}}
    );
    CHECK(true == std::abs(15.0576923077 - result) < 0.0001);

    std::string const expression_factorization = "4(3.25x)";
    double const      result_factorization     = mast::evaluate_ast(
        *parser.expression_to_ast(expression_factorization, variables),
        std::map<char, double>{{'x', 5.}}
    );
    CHECK(result_factorization == 65);

    std::string const expression_var_pow = "(4x^2 + 23.5)*(3^2) / (1 + x^2)";
    double const      result_var_pow     = mast::evaluate_ast(
        *parser.expression_to_ast(expression_var_pow, variables),
        std::map<char, double>{{'x', 5.}}
    );
    CHECK(result_var_pow == 42.75);
}
