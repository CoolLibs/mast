#include "OperatorConcrete.h"

namespace mast {

OperatorConcrete::OperatorConcrete(const std::string& symbol, const bool& right_associative, const int8_t& precedence)
    : _symbol(symbol), _right_associative(right_associative), _precedence(precedence)
{
}

auto OperatorConcrete::compare_precedence(IOperator* o) -> int
{
    if (auto* other = dynamic_cast<OperatorConcrete*>(o))
    {
        return (_precedence > other->_precedence) ? 1 : (other->_precedence == _precedence) ? 0
                                                                                            : -1;
    }
    return -o->compare_precedence(this);
}

} // namespace mast