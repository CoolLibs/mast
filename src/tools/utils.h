#pragma once

#include <map>
#include <stack>

template<typename T>
auto pop_and_get_top(std::stack<T>& stack) -> T
{
    T top = stack.top();
    stack.pop();
    return top;
}