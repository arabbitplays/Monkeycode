#include "model/CppCodingExpressions.hpp"

#include "generator/ExpressionGenerator.hpp"
#include "util/StringGenerationUtil.hpp"

std::string VariableNameLiteral::eval() {
    RNG rng{};
    return StringGenerationUtil::randomNWords(rng, rng.getUInt(1, 3), '_');
}

std::string NumberLiteral::eval() {
    RNG rng{};
    return StringGenerationUtil::randomNDigitString(rng, rng.getUInt(3, 7));
}

std::string BracketExpression::eval() {
    ExpressionGenerator generator;
    RNG rng{};
    auto bracket_pair = StringGenerationUtil::randomBracketPair(rng);
    std::shared_ptr<Expression> expr = generator.generate(rng);
    return bracket_pair.first + " " + expr->eval() + " " + bracket_pair.second;
}

std::string StartExpression::eval() {
    std::string result = "";
    for (uint32_t i = 0; i < 10; i++) {
        std::shared_ptr<Expression> expr = std::make_shared<BracketExpression>();
        result += expr->eval() + "\n";
    }
    return result;
}
