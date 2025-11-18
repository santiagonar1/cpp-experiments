#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <allocator.hpp>
#include <ranges>

using testing::Eq;

TEST(AnAllocator, RequiresAnArena) {
    auto arena = SimpleArena<512>{};
    const auto allocator = Allocator<int, SimpleArena<512>>{arena};
}

TEST(AnAllocator, UsesByDefaultSimpleArena) {
    auto simple_arena = SimpleArena<1024>{};
    const auto allocator = Allocator<int>(simple_arena);
}

TEST(AnAllocator, Allocates) {
    auto simple_arena = SimpleArena<1024>{};
    const auto allocator = Allocator<int>(simple_arena);
    auto values = std::vector<int, Allocator<int>>{allocator};

    for (int i = 0; i < 10; ++i) { values.emplace_back(i); }

    EXPECT_THAT(values, Eq(std::vector{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, allocator}));
}