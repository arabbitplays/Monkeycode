#ifndef MONKEYCODE_LITERAL_HPP
#define MONKEYCODE_LITERAL_HPP
#include <memory>

#include "include/model/Expression.hpp"

class Literal : public Expression {
public:
  std::string eval() override = 0;
};

#endif // MONKEYCODE_LITERAL_HPP