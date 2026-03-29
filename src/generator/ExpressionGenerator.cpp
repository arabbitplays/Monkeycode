#include "generator/ExpressionGenerator.hpp"

#include "model/CppCodingExpressions.hpp"
#include "util/RandomUtil.hpp"

ExpressionGenerator::ExpressionGenerator() {
    addGenerator([] { return std::make_shared<VariableNameLiteral>(); });
    addGenerator([] { return std::make_shared<NumberLiteral>(); });
}

void ExpressionGenerator::addGenerator(Generator gen) {
    generators.push_back(std::move(gen));
}

std::shared_ptr<Expression> ExpressionGenerator::generate(RNG& rng) {
    if (generators.empty()) {
        return nullptr;
    }

    return generators[rng.getUInt(generators.size() - 1)]();
}
