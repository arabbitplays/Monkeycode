#ifndef MONKEYCODE_TESTRUNNER_HPP
#define MONKEYCODE_TESTRUNNER_HPP
#include <cstdint>
#include <string>
#include <vector>

enum CharState { UNWRITTEN = 0, CORRECT, FALSE, JUMPED_OVER };

struct CharNode {
    char c;
    char written_c;
    CharState state;
};

typedef std::vector<CharNode> CharSet;
typedef std::pair<uint32_t, uint32_t> UVec2;

class TestRunner {
  public:
    explicit TestRunner(const std::string &test_text);

    void run();
    void moveToNextWord();
    void moveToNextLine();
    void moveBack();

  private:
    void initCharSet(const std::string &test_text);
    void adjustCursorPosToCurrChar();
    static void moveTerminalCursorPos(UVec2 pos);
    void printCharNode(const CharNode &node);
    static void clearScreen();

    CharSet char_set{};
    UVec2 cursor_pos{ 1, 1 };
    uint32_t curr_char = 0;
};

#endif // MONKEYCODE_TESTRUNNER_HPP
