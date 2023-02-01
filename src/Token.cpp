#include "Token.h"

namespace mast {

Token::Token(Token::Type type, std::string content, OperatorConfig operator_config)
    : _type(type), _content(content), _operator_config(operator_config)
{}
} // namespace mast