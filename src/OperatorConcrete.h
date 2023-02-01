#pragma once

#include "IOperator.h"

namespace mast {

class OperatorConcrete : public IOperator {
public:
    OperatorConcrete(const std::string& symbol, const bool& right_associative, const int8_t precedence);

    bool is_right_associative() const override { return _right_associative; };
    std::string get_symbol() const override { return _symbol; };
    int8_t compare_precedence(IOperator*) const override;

private:
    const std::string _symbol;
    const bool        _right_associative;
    const int8_t      _precedence;
};

auto operator<<(std::ostream& os, const OperatorConcrete& operatorConcrete) -> std::ostream&
{
    os << operatorConcrete.get_symbol();
    return os;
}

} // namespace mast
