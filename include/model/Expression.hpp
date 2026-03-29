#ifndef MONKEYCODE_EXPRESSION_HPP
#define MONKEYCODE_EXPRESSION_HPP
#include <string>

class Expression {
  public:
    virtual ~Expression() = default;

    virtual std::string eval() = 0;
};
#endif // MONKEYCODE_EXPRESSION_HPP