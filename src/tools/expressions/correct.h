#pragma once

#include <list>
#include <vector>
#include "../../Tokenizer.h"

namespace mast {

void correct_token_list(std::list<Token>& tokens_list);
void throw_error_on_multiple_dots_number(std::string token_content);
void handle_implicit_multiplications(std::list<Token>& tokens_list, std::list<Token>::const_iterator current);
// ToDo : Check if function separator is OK

} // namespace mast
