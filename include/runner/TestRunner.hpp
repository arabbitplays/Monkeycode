#ifndef MONKEYCODE_TESTRUNNER_HPP
#define MONKEYCODE_TESTRUNNER_HPP
#include "util/TimeUtil.hpp"

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>

enum CharState { UNWRITTEN = 0, CORRECT, FALSE, JUMPED_OVER, OVERFLOW };

struct CharNode {
    char c;
    char written_c;
    CharState state;
};

struct WordNode {
    std::vector<CharNode> char_nodes;
    CharNode last_char;
};

typedef std::vector<WordNode> WordSet;
typedef std::pair<uint32_t, uint32_t> UVec2;

struct TestResult {
    WordSet word_set;
    Milliseconds duration;
    float accuracy;
};

class TestRunner {
  public:
    TestRunner() = default;

    TestResult run(const std::string &test_string);

  private:
    void resetCursors();
    void initWordSet(const std::string &test_text);

    void refreshText();

    CharNode &getCurrCharNode();
    CharNode &nextCharNode();
    CharNode &prevCharNode();

    void adjustCursorPosToCurrChar() const;
    static void moveTerminalCursorPos(UVec2 pos);

    void moveToNextWord();
    void moveToNextLine();
    void moveBack();

    static void printWordNode(const WordNode &node);
    static void printCharNode(const CharNode &node);

    static void clearScreen();

    WordSet word_set;

    UVec2 cursor_pos{1, 1};
    uint32_t curr_char = 0;
    uint32_t curr_word = 0;
};

#endif // MONKEYCODE_TESTRUNNER_HPP
