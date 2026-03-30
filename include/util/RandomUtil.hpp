#ifndef MONKEYCODE_RENDOMUTIL_HPP
#define MONKEYCODE_RENDOMUTIL_HPP

#include <iostream>
#include <random>

class RNG {
  public:
    // Default: non-deterministic seed
    RNG() : engine(std::random_device{}()) {}

    RNG(uint32_t seed) : engine(seed) {}

    void seed(uint32_t s) { engine.seed(s); }

    std::mt19937 &get() { return engine; }

    uint32_t getUInt(uint32_t n) {
        std::uniform_int_distribution<int> digit(0, n);
        return digit(engine);
    }

    uint32_t getUInt(uint32_t low, uint32_t high) {
        std::uniform_int_distribution<int> digit(low, high);
        return digit(engine);
    }

  private:
    std::mt19937 engine;
};

#endif // MONKEYCODE_RENDOMUTIL_HPP
