#include "generator/ExpressionGenerator.hpp"

#include "model/CppCodingExpressions.hpp"
#include "util/RandomUtil.hpp"

ExpressionGenerator::ExpressionGenerator() {
    addLiteralGenerator([] { return std::make_shared<VariableNameLiteral>(); });
    addLiteralGenerator([] { return std::make_shared<NumberLiteral>(); });

    addGenerator([] { return std::make_shared<EquationExpression>(); });
    addGenerator([] { return std::make_shared<BracketExpression>(); });
}

std::shared_ptr<Expression> ExpressionGenerator::generateExpression(RNG &rng) {
    if (expressionGenerators.empty()) {
        return nullptr;
    }
    return expressionGenerators[rng.getUInt(expressionGenerators.size() - 1)]();
}
std::shared_ptr<Expression> ExpressionGenerator::generateLiteral(RNG &rng) {
     if (literalGenerators.empty()) {
        return nullptr;
    }
    return literalGenerators[rng.getUInt(literalGenerators.size() - 1)]();
}

void ExpressionGenerator::addLiteralGenerator(Generator gen) {
    literalGenerators.push_back(gen);
    expressionGenerators.push_back(gen);
}

void ExpressionGenerator::addGenerator(Generator gen) {
    expressionGenerators.push_back(gen);
}
