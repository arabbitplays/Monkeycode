#include "model/CppCodingExpressions.hpp"

#include "generator/ExpressionGenerator.hpp"
#include "util/StringGenerationUtil.hpp"

std::string VariableNameLiteral::eval() {
    RNG rng{};
    uint32_t N = rng.getUInt(1, 3);
    CaseStyle style = StringGenerationUtil::randomCaseStyle(rng);

    std::string result;
    for (uint32_t i = 0; i < N; ++i) {
        std::string next_word = StringGenerationUtil::randomWord(rng);
        switch (style) {
        case SNAKE_CASE:
            if (i != 0) {
                result += "_";
            }
            result += next_word;
            break;
        case UPPER_SNAKE_CASE:
            if (i != 0) {
                result += "_";
            }
            result += StringUtil::toUpper(next_word);
            break;
        case CAMEL_CASE:
            result += i == 0 ? next_word : StringUtil::capitalize(next_word);
            break;
        case UPPER_CAMEL_CASE:
            result += StringUtil::capitalize(next_word);
            break;
        case COUNT_HELPER:
            break;
        }
    }

    return result;
}

std::string NumberLiteral::eval() {
    RNG rng{};
    return StringGenerationUtil::randomNDigitString(rng, rng.getUInt(3, 7));
}

std::string EquationExpression::eval() {
    ExpressionGenerator generator;
    RNG rng{};
    uint32_t N = rng.getUInt(2, 4);

    std::string result;
    for (uint32_t i = 0; i < N; ++i) {
        const std::shared_ptr<Expression> next_literal =
            generator.generateLiteral(rng);
        std::string symbol = StringGenerationUtil::randomMathSymbol(rng);

        if (i != 0) {
            result += " " + symbol + " ";
        }
        result += next_literal->eval();
    }

    return result;
}

std::string BracketExpression::eval() {
    ExpressionGenerator generator;
    RNG rng{};
    auto bracket_pair = StringGenerationUtil::randomBracketPair(rng);
    std::shared_ptr<Expression> expr = generator.generateExpression(rng);
    return bracket_pair.first + " " + expr->eval() + " " + bracket_pair.second;
}

std::string StartExpression::eval() {
    ExpressionGenerator generator;
    RNG rng{};

    std::string result;
    for (uint32_t i = 0; i < 1; i++) {
        std::shared_ptr<Expression> expr = generator.generateExpression(rng);
        result += expr->eval() + "\n";
    }
    return result;
}
