#include "random_generator.hpp"

#include <random>

auto get_random_int(const int min, const int max) -> int {
    auto device = std::random_device{};
    auto engine = std::default_random_engine{device()};
    auto dist = std::uniform_int_distribution{min, max};
    return dist(engine);
}