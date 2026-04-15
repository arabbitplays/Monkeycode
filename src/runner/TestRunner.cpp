#include "../../include/runner/TestRunner.hpp"

#include <cassert>
#include <chrono>
#include <iostream>
#include <termios.h>
#include <unistd.h>

char getch() {
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);

    termios newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // disable buffering + echo

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char c;
    read(STDIN_FILENO, &c, 1);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore

    return c;
}

TestResult TestRunner::run(const std::string &test_string) {
    initWordSet(test_string);
    resetCursors();

    auto start = std::chrono::high_resolution_clock::now();
    uint32_t correct_pressed_chars = 0;
    uint32_t wrong_pressed_chars = 0;

    while (curr_word != word_set.size() - 1 ||
           curr_char != word_set[word_set.size() - 1].char_nodes.size()) {

        refreshText();
        adjustCursorPosToCurrChar();

        char c = getch();

        CharNode &currCharNode = getCurrCharNode();
        if (c == currCharNode.c) {
            currCharNode.state = CORRECT;
            currCharNode.written_c = c;
            nextCharNode();
            correct_pressed_chars++;
        } else if (c == 127 || c == '\b') {
            prevCharNode();
            if (getCurrCharNode().state == OVERFLOW) {
                word_set[curr_word].char_nodes.pop_back();
            } else {
                moveBack();
                CharNode &node = getCurrCharNode();
                node.state = UNWRITTEN;
            }
        } else {
            wrong_pressed_chars++;
            if (c == ' ') {
                moveToNextWord();
            } else if (c == '\n') {
                moveToNextLine();
            } else {
                if (curr_char == word_set[curr_word].char_nodes.size()) {
                    word_set[curr_word].char_nodes.push_back({c, c, OVERFLOW});
                    nextCharNode();
                } else {
                    currCharNode.state = FALSE;
                    currCharNode.written_c = c;
                    nextCharNode();
                }
            }
        }
    }
    refreshText();
    std::cout << "\n\n" << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    Milliseconds duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    float accuracy = static_cast<float>(correct_pressed_chars) / static_cast<float>(correct_pressed_chars + wrong_pressed_chars);
    return { word_set, duration, accuracy };
}

void TestRunner::resetCursors() {
    cursor_pos = {1, 1};
    curr_char = 0;
    curr_word = 0;
}


void TestRunner::refreshText() {
    clearScreen();
    moveTerminalCursorPos({1, 1});
    for (const auto &word_node : word_set) {
        printWordNode(word_node);
    }
}

CharNode &TestRunner::getCurrCharNode() {
    assert(curr_char <= word_set[curr_word].char_nodes.size());
    if (curr_char == word_set[curr_word].char_nodes.size()) {
        return word_set[curr_word].last_char;
    }
    return word_set[curr_word].char_nodes[curr_char];
}

CharNode &TestRunner::nextCharNode() {
    if (curr_char == word_set[curr_word].char_nodes.size()) {
        curr_word++;
        curr_char = 0;
    } else {
        curr_char++;
    }
    return getCurrCharNode();
}

CharNode &TestRunner::prevCharNode() {
    if (curr_char == 0) {
        if (curr_word == 0) {
            return getCurrCharNode();
        }

        curr_word--;
        curr_char = word_set[curr_word].char_nodes.size();
    } else {
        curr_char--;
    }
    return getCurrCharNode();
}

void TestRunner::moveToNextWord() {
    for (auto &char_node : word_set[curr_word].char_nodes) {
        if (char_node.state == UNWRITTEN) {
            char_node.state = JUMPED_OVER;
        }
    }
    word_set[curr_word].last_char.state = JUMPED_OVER;
    curr_word++;
    curr_char = 0;
}

void TestRunner::moveToNextLine() {
    while (word_set[curr_word].last_char.c != '\n') {
        moveToNextWord();
    }
    moveToNextWord();
}

void TestRunner::moveBack() {
    bool moved = false;
    while (getCurrCharNode().state == JUMPED_OVER) {
        getCurrCharNode().state = UNWRITTEN;
        prevCharNode();
        moved = true;
    }

    if (moved && getCurrCharNode().state != UNWRITTEN) {
        nextCharNode();
    }
}

void TestRunner::initWordSet(const std::string &test_text) {
    word_set.push_back({{}, {}});
    for (const auto &c : test_text) {
        if (c == ' ' || c == '\n') {
            word_set[word_set.size() - 1].last_char = {c, UNWRITTEN};
            word_set.push_back({{}, {}});
        } else {
            word_set[word_set.size() - 1].char_nodes.push_back({c, UNWRITTEN});
        }
    }
}

void TestRunner::adjustCursorPosToCurrChar() const {
    uint32_t x = 1;
    uint32_t y = 1;
    for (uint32_t i = 0;
         static_cast<int32_t>(i) < static_cast<int32_t>(curr_word); i++) {
        if (word_set[i].last_char.c == '\n') {
            y++;
            x = 1;
        } else {
            x += word_set[i].char_nodes.size() + 1;
        }
    }
    x += curr_char;
    moveTerminalCursorPos({x, y});
}

void TestRunner::moveTerminalCursorPos(UVec2 pos) {
    std::cout << "\033[" << pos.second << ";" << pos.first << "H" << std::flush;
}

void TestRunner::printWordNode(const WordNode &node) {
    for (const auto &c : node.char_nodes) {
        printCharNode(c);
    }
    printCharNode(node.last_char);
}

void TestRunner::printCharNode(const CharNode &node) {
    switch (node.state) {
    case UNWRITTEN:
        std::cout << node.c;
        break;
    case CORRECT:
        std::cout << "\033[32m" << node.written_c << "\033[0m";
        break;
    case FALSE:
        std::cout << "\033[31m" << node.written_c << "\033[0m";
        break;
    case OVERFLOW:
        std::cout << "\033[34m" << node.written_c << "\033[0m";
        break;
    case JUMPED_OVER:
        std::cout << "\033[33m" << node.c << "\033[0m";
        break;
    }
}

void TestRunner::clearScreen() { std::cout << "\033[2J\033[H" << std::flush; }