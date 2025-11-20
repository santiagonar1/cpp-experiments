#include <iostream>
#include <vector>

#include <allocator.hpp>
#include <object_arena.hpp>
#include <simple_arena.hpp>

struct Bar {
    Bar() { std::cout << "constructor bar called" << std::endl; }
    ~Bar() { std::cout << "destructor bar called" << std::endl; }
};

struct Foo {
    Foo() { std::cout << "constructor foo called" << std::endl; }
    ~Foo() { std::cout << "destructor foo called" << std::endl; }
};

int main() {
    auto simple_arena = SimpleArena<1024>{};
    std::cout << "\n\n ======== Simple Arena ========\n\n";

    std::cout << "allocated buffer at " << simple_arena._buffer << " ("
              << sizeof simple_arena._buffer << " bytes)\n";

    // Allocate chars
    if (auto *p = simple_arena.create<char>(1)) {
        *p = 'a';
        std::cout << "allocated a char at " << (void *) p << '\n';
    }

    // Allocate one int
    if (auto *p = simple_arena.create<int>(1)) {
        *p = 1;
        std::cout << "allocated an int at " << (void *) p << '\n';
    }

    // Allocate chars
    if (auto *p = simple_arena.create<char>(1)) {
        *p = 'a';
        std::cout << "allocated a char at " << (void *) p << '\n';
    }

    // Allocate chars
    if (auto *p = simple_arena.create<char>(1)) {
        *p = 'a';
        std::cout << "allocated a char at " << (void *) p << '\n';
    }

    std::cout << "\n\n ======== Allocator ========\n\n";

    const auto allocator = Allocator<int>{simple_arena};
    auto values = std::vector<int, Allocator<int>>{allocator};

    std::cout << "capacity arena before: " << simple_arena.capacity() << '\n';
    for (int i = 0; i < 10; ++i) { values.emplace_back(i); }

    std::cout << values.size() << " values allocated\n";
    std::cout << "capacity arena after: " << simple_arena.capacity() << '\n';
    auto delimiter = std::string{};
    std::cout << "[";
    for (const auto &value: values) { std::cout << std::exchange(delimiter, ", ") << value; }
    std::cout << "]\n";

    std::cout << "\n\n ======== Allocator with object ========\n\n";
    {
        const auto object_allocator = Allocator<Bar>{simple_arena};
        auto dummy_values = std::vector<Bar, Allocator<Bar>>{object_allocator};
        dummy_values.emplace_back();
    }

    std::cout << "\n\n ======== Object Arena ========\n\n";

    auto object_arena = ObjectArena{1024};

    auto *bar = object_arena.create<Bar>();
    auto *foo = object_arena.create<Foo>();

    return 0;
}