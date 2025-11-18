#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <simple_arena.hpp>

TEST(SimpleArena, CanBeUsedToAllocateMemory) {
    auto arena = SimpleArena<512>{};
    auto *ptr = arena.create<char>(1);

    EXPECT_NE(ptr, nullptr);
}