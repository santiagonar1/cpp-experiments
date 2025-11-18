#include <iostream>
#include <vector>

#include <allocator.hpp>
#include <simple_arena.hpp>

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


    return 0;
}