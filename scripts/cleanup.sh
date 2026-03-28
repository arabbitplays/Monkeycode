#!/usr/bin/env bash

echo "-------------------- Running clang tidy ---------------------------"
clang-tidy -p buildDir $(find src -name "*.cpp") --fix -checks=readability-*,bugprone-*

echo "-------------------- Running clang format ---------------------------"
find src include -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i