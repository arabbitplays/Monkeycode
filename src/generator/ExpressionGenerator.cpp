#include "generator/ExpressionGenerator.hpp"

#include "model/CppCodingExpressions.hpp"

ExpressionGenerator::ExpressionGenerator() {
  addGenerator([] { return std::make_shared<VariableName>(); });
}

void ExpressionGenerator::addGenerator(Generator gen) {
  generators.push_back(std::move(gen));
}

std::shared_ptr<Expression> ExpressionGenerator::generate() {
  if (generators.empty()) {
    return nullptr;
  }

  std::uniform_int_distribution<size_t> dist(0, generators.size() - 1);
  return generators[dist(rng)]();
}
