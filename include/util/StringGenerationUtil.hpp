#ifndef MONKEYCODE_STRINGGENERATIONUTIL_HPP
#define MONKEYCODE_STRINGGENERATIONUTIL_HPP
#include "RandomUtil.hpp"
#include "StringUtil.hpp"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>

enum CaseStyle {
    SNAKE_CASE,
    UPPER_SNAKE_CASE,
    CAMEL_CASE,
    UPPER_CAMEL_CASE,
    COUNT_HELPER
};

class StringGenerationUtil {
  public:
    static CaseStyle randomCaseStyle(RNG &rng) {
        return static_cast<CaseStyle>(
            rng.getUInt(static_cast<int>(COUNT_HELPER) - 1));
    }

    static std::string randomNDigitString(RNG &rng, uint32_t N) {
        std::string result;
        result += char('0' + rng.getUInt(1, 9));

        for (int i = 1; i < N; ++i) {
            result += char('0' + rng.getUInt(9));
        }

        return result;
    }

    static std::string randomWord(RNG &rng) {
        std::string result;
        auto word_list = getWordList();
        assert(!word_list.empty());

        return word_list[rng.getUInt(word_list.size() - 1)];
    }

    static std::string randomMathSymbol(RNG &rng) {
        std::vector<std::string> symbols{
            "+", "-", "*", "/", "%", "|"
        };

        return symbols[rng.getUInt(symbols.size() - 1)];
    }

    static std::pair<std::string, std::string> randomBracketPair(RNG &rng) {
        std::vector<std::pair<std::string, std::string>> brackets{
            {"{", "}"}, {"(", ")"},   {"[", "]"},
            {"<", ">"}, {"\'", "\'"}, {"\"", "\""},
        };

        return brackets[rng.getUInt(brackets.size() - 1)];
    }

  private:
    static std::vector<std::string> &getWordList() {
        static std::vector<std::string> lines = []() {
            std::ifstream file("../resources/eng_10000.txt");
            std::vector<std::string> result;

            std::string line;
            while (std::getline(file, line)) {
                result.push_back(line);
            }

            return result;
        }();

        return lines;
    }
};
#endif // MONKEYCODE_STRINGGENERATIONUTIL_HPP
