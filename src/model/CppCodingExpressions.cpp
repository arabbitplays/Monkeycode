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

    std::string first_num =
        StringGenerationUtil::randomNDigitString(rng, rng.getUInt(2, 5));
    std::string second_num =
        StringGenerationUtil::randomNDigitString(rng, rng.getUInt(2, 5));

    if (rng.getUInt(0, 1)) {
        return first_num + "." + second_num + "f";
    } else {
        return first_num + "," + second_num;
    }
}
std::string TypeLiteral::eval() {
    RNG rng{};
    std::vector<std::string> basic_types{"uint32_t",
                                         "int32_t",
                                         "int64_t",
                                         "uint64_t",
                                         "uint8_t",
                                         "int8_t",
                                         "std::filesystem::path"
                                         "std::string"};

    std::vector<std::string> generic_types{
        "std::vector",  "std::unordered_map", "std::unordered_set",
        "std::deque",   "std::shared_ptr",    "std::unique_ptr",
        "std::weak_ptr"};

    const uint32_t MAX_DEPTH = 3;

    std::string result;
    std::string closing_brackets;
    for (uint32_t i = 0; i < MAX_DEPTH; ++i) {
        if (rng.getUInt(0, 1) == 0) {
            return result +
                   basic_types[rng.getUInt(0, basic_types.size() - 1)] +
                   closing_brackets;
        } else {
            const std::string &type =
                generic_types[rng.getUInt(0, generic_types.size() - 1)];
            result += type + "<";
            closing_brackets += ">";
        }
    }
    return result + closing_brackets;
}

std::string PtrExpression::eval() {
    VariableNameLiteral first_var{};
    VariableNameLiteral second_var{};
    return first_var.eval() + "->" + second_var.eval();
}

std::string SpecialSymbolLiteral::eval() {
    RNG rng{};
    return StringGenerationUtil::randomSpecialSymbol(rng);
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

std::string MacroExpression::eval() {
    RNG rng{};
    uint32_t N = rng.getUInt(0, 3);
    if (N == 0) {
        return "#include \"" + StringGenerationUtil::randomWord(rng) + "\"";
    } else if (N == 1) {
        return "#ifndef " +
               StringUtil::toUpper(StringGenerationUtil::randomWord(rng));
    } else if (N == 2) {
        return "#define " +
               StringUtil::toUpper(StringGenerationUtil::randomWord(rng));
    } else if (N == 3) {
        return "#endif";
    }
    return "";
}

std::string StartExpression::eval() {
    ExpressionGenerator generator;
    RNG rng{};

    const uint32_t TARGET_LINE_LENGTH = 30;
    const uint32_t LINE_COUNT = 15;

    std::string result;
    for (uint32_t i = 0; i < LINE_COUNT; i++) {

        uint32_t curr_line_length = 0;
        while (curr_line_length < TARGET_LINE_LENGTH) {

            std::shared_ptr<Expression> expr =
                generator.generateExpression(rng);
            std::string evaluated = expr->eval();

            if (curr_line_length != 0) {
                result += " ";
            }
            result += evaluated;
            curr_line_length += evaluated.length();
        }
        result += ";\n";
    }
    return result;
}
