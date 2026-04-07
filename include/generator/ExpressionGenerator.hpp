#ifndef MONKEYCODE_EXPRESSIONGENERATOR_HPP
#define MONKEYCODE_EXPRESSIONGENERATOR_HPP
#include <functional>
#include <memory>
#include <random>

#include "model/Expression.hpp"
#include "model/Literal.hpp"
#include "util/RandomUtil.hpp"

class ExpressionGenerator {
  public:
    using Generator = std::function<std::shared_ptr<Expression>()>;

    ExpressionGenerator();

    std::shared_ptr<Expression> generateExpression(RNG &rng);
    std::shared_ptr<Expression> generateLiteral(RNG &rng);

  private:
    void addLiteralGenerator(Generator gen);
    void addGenerator(Generator gen);

    std::vector<Generator> expressionGenerators;
    std::vector<Generator> literalGenerators;
    std::mt19937 rng;
};

#endif // MONKEYCODE_EXPRESSIONGENERATOR_HPP
