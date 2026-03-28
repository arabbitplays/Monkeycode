#ifndef MONKEYCODE_EXPRESSIONGENERATOR_HPP
#define MONKEYCODE_EXPRESSIONGENERATOR_HPP
#include <functional>
#include <memory>
#include <random>

#include "model/Expression.hpp"

class ExpressionGenerator {
public:
  using Generator = std::function<std::shared_ptr<Expression>()>;

  ExpressionGenerator();

  std::shared_ptr<Expression> generate();

private:
  void addGenerator(Generator gen);

  std::vector<Generator> generators;
  std::mt19937 rng;
};

#endif // MONKEYCODE_EXPRESSIONGENERATOR_HPP
