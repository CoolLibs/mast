#pragma once

#include <vector>
#include "../../Tokenizer.h"

namespace mast {

void correct_token_list(std::vector<Token>& tokens_list);

void throw_error_on_multiple_dots_number(std::string token_content);
void handle_implicit_multiplication(std::vector<Token>& tokens_list, std::vector<Token>::const_iterator current);

} // namespace mast
