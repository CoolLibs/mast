#pragma once

#include <map>
#include <stack>

template<typename T>
auto get_top_and_pop(std::stack<T>& stack) -> T
{
    T top = stack.top();
    stack.pop();
    return top;
}