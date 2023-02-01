#include "OperatorConcrete.h"

namespace mast {

OperatorConcrete::OperatorConcrete(const std::string& symbol, const bool& right_associative, const int8_t& precedence)
    : _symbol(symbol), _right_associative(right_associative), _precedence(precedence)
{
}

} // namespace mast