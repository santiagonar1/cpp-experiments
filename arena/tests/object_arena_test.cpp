#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <object_arena.hpp>

using testing::Eq;

enum class State {
    Undefined,
    Created,
    Destroyed,
};

class Bar {
public:
    explicit Bar(State &state) : _state{state} { _state = State::Created; }
    ~Bar() { _state = State::Destroyed; }

private:
    State &_state;
};

TEST(ObjectArena, CanBeUsedToAllocateMemory) {
    auto arena = ObjectArena{512};
    auto *ptr = arena.create<char>(1);

    EXPECT_NE(ptr, nullptr);
}

TEST(ObjectArena, UsesProperMemoryAlignment) {
    auto arena = ObjectArena{512};

    auto *ptr_char = arena.create<char>(1);
    auto *ptr_int = arena.create<int>(1);

    EXPECT_EQ(reinterpret_cast<std::uintptr_t>(ptr_char) % alignof(char), 0);
    EXPECT_EQ(reinterpret_cast<std::uintptr_t>(ptr_int) % alignof(int), 0);
}

TEST(ObjectArena, CanBeUsedForComplexDatatypes) {
    auto arena = ObjectArena{512};
    auto state{State::Undefined};
    auto *bar = arena.create<Bar>(state);
    EXPECT_THAT(state, Eq(State::Created));
}

TEST(ObjectArena, CallsDestructorWhenArenaIsDestroyed) {
    auto state{State::Undefined};
    {
        auto arena = ObjectArena{512};
        auto *bar = arena.create<Bar>(state);
    }
    EXPECT_THAT(state, Eq(State::Destroyed));
}