#ifndef MONKEYCODE_CPPCODINGEXPRESSIONS_HPP
#define MONKEYCODE_CPPCODINGEXPRESSIONS_HPP
#include "Literal.hpp"

class VariableName final : public Literal {
public:
  std::string eval() override;
};

class BracketExpression final : public Expression {
public:
  std::string eval() override;
};

class StartExpression final : public Expression {
public:
  std::string eval() override;
};
#endif // MONKEYCODE_CPPCODINGEXPRESSIONS_HPP