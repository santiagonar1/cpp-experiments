#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <allocator.hpp>
#include <simple_arena.hpp>

enum class State {
    Undefined,
    Created,
    Destroyed,
};


std::ostream &operator<<(std::ostream &os, State state) {
    switch (state) {
        case State::Undefined:
            return os << "Undefined";
        case State::Created:
            return os << "Created";
        case State::Destroyed:
            return os << "Destroyed";
    }
    return os << "Unknown";
}


class Bar {
public:
    explicit Bar(State &state) : _state{state} { _state = State::Created; }
    ~Bar() { _state = State::Destroyed; }

private:
    State &_state;
};

using ::testing::Eq;

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

TEST(SimpleArena, CanBeUsedWithAnAllocatorWithComplexObjects) {
    auto states = std::vector{State::Undefined, State::Undefined, State::Undefined};

    {
        auto simple_arena = SimpleArena<1024>{};
        const auto allocator = Allocator<Bar>(simple_arena);
        auto values = std::vector<Bar, Allocator<Bar>>{allocator};
        values.reserve(states.size());
        for (auto &state: states) {
            values.emplace_back(state);
        }
        EXPECT_THAT(states, Eq(std::vector{State::Created, State::Created, State::Created}));
    }

    EXPECT_THAT(states, Eq(std::vector{State::Destroyed, State::Destroyed, State::Destroyed}));
}