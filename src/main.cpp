#include <iostream>
#include <memory>

#include "include/model/CppCodingExpressions.hpp"

int main(int argc, char *argv[]) {
    std::shared_ptr<Expression> start = std::make_shared<StartExpression>();
    std::string generated_text = start->eval();
    std::cout << generated_text << std::endl;
}
