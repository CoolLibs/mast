#include "OperatorConcrete.h"

namespace mast {
int8_t OperatorConcrete::compare_precedence(IOperator* comparedOperator) const
{
    // ToDo: Doesn't work
    if (IOperator* other = dynamic_cast<IOperator*>(comparedOperator)) {
        return (_precedence > other->_precedence) ? 1 :
               (other->_precedence == _precedence) ? 0 : -1;
    } else {
        return -comparedOperator->compare_precedence(this);
    }
}
} // namespace mast