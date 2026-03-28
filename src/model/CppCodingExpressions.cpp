#include "model/CppCodingExpressions.hpp"

#include "generator/ExpressionGenerator.hpp"

std::string VariableName::eval() { return "foo"; }

std::string BracketExpression::eval() {
  ExpressionGenerator generator;
  std::shared_ptr<Expression> expr = generator.generate();
  return expr->eval();
}

std::string StartExpression::eval() {
  std::shared_ptr<Expression> expr = std::make_shared<BracketExpression>();
  return "{ " + expr->eval() + " }";
}
