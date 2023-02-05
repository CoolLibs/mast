#pragma once

#include "IOperator.h"

namespace mast {

class OperatorConcrete : public IOperator {
public:
    virtual ~OperatorConcrete() = default;
    OperatorConcrete(const std::string& symbol, const bool& right_associative, const int8_t& precedence);

    [[nodiscard]] auto is_right_associative() const -> bool override { return _right_associative; };
    [[nodiscard]] auto get_symbol() const -> std::string override { return _symbol; };
    [[nodiscard]] auto get_precedence() const -> int8_t override { return _precedence; };
    auto compare_precedence(IOperator* o) -> int override;

private:
    const std::string _symbol;
    const bool        _right_associative;
    const int8_t      _precedence;
};

} // namespace mast
