#include "../../include/runner/TestRunner.hpp"
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

TestRunner::TestRunner(const std::string &test_text) { initCharSet(test_text); }

void TestRunner::run() {
    clearScreen();

    while (curr_char != char_set.size()) {
        moveTerminalCursorPos({1, 1});
        for (const auto &char_node : char_set) {
            printCharNode(char_node);
        }
        adjustCursorPosToCurrChar();

        char c = getch();

        if (c == char_set[curr_char].c) {
            char_set[curr_char].state = CORRECT;
            char_set[curr_char].written_c = c;
            curr_char++;
        } else if (c == 127 || c == '\b') {
            curr_char--;
            char_set[curr_char].state = UNWRITTEN;
            moveBack();
        } else {

            if (c == ' ') {
                moveToNextWord();
            } else if (c == '\n') {
                moveToNextLine();
            } else {
                char_set[curr_char].state = FALSE;
                char_set[curr_char].written_c = c;
                curr_char++;
            }
        }
    }
}

void TestRunner::moveToNextWord() {
    while (char_set[curr_char].c != ' ') {
        char_set[curr_char].state = JUMPED_OVER;
        curr_char++;
    }
    char_set[curr_char].state = JUMPED_OVER;
    curr_char++;
}

void TestRunner::moveToNextLine() {
     while (char_set[curr_char].c != '\n') {
        char_set[curr_char].state = JUMPED_OVER;
        curr_char++;
    }
    char_set[curr_char].state = JUMPED_OVER;
    curr_char++;
}

void TestRunner::moveBack() {
    while (curr_char != 0 && char_set[curr_char - 1].state == JUMPED_OVER) {
        curr_char--;
        char_set[curr_char].state = UNWRITTEN;
    }
}

void TestRunner::initCharSet(const std::string &test_text) {
    char_set.reserve(test_text.size());
    for (const auto &c : test_text) {
        char_set.push_back({c, UNWRITTEN});
    }
}

void TestRunner::adjustCursorPosToCurrChar() {
    uint32_t x = 1;
    uint32_t y = 1;
    for (uint32_t i = 0; i < curr_char; i++) {
        if (char_set[i].c == '\n') {
            y++;
            x = 1;
        } else {
            x++;
        }
    }
    moveTerminalCursorPos({x, y});
}

void TestRunner::moveTerminalCursorPos(UVec2 pos) {
    std::cout << "\033[" << pos.second << ";" << pos.first << "H" << std::flush;
}

void TestRunner::printCharNode(const CharNode &node) {
    switch (node.state) {
    case UNWRITTEN:
        std::cout << node.c;
        break;
    case CORRECT:
        std::cout << "\033[32m" << node.written_c << "\033[0m";
        break;
    case FALSE: {
        std::string char_to_print =
            node.written_c == ' ' ? "█" : std::string(1, node.written_c);
        std::cout << "\033[31m" << char_to_print << "\033[0m";
        break;
    }
    case JUMPED_OVER:
        std::cout << "\033[33m" << node.c << "\033[0m";
        break;
    }
}

void TestRunner::clearScreen() { std::cout << "\033[2J\033[H" << std::flush; }
