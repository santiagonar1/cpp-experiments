#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <simple_arena.hpp>

TEST(SimpleArena, CanBeUsedToAllocateMemory) {
    auto arena = SimpleArena<512>{};
    auto *ptr = arena.create<char>(1);

    EXPECT_NE(ptr, nullptr);
}

TEST(SimpleArena, UsesProperMemoryAlignment) {
    auto arena = SimpleArena<512>{};

    auto* ptr_char = arena.create<char>(1);
    auto* ptr_int = arena.create<int>(1);

    EXPECT_EQ(reinterpret_cast<std::uintptr_t>(ptr_char) % alignof(char), 0);
    EXPECT_EQ(reinterpret_cast<std::uintptr_t>(ptr_int) % alignof(int), 0);
}