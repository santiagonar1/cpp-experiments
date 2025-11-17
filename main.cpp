#include <iostream>

#include <simple_arena.hpp>

int main() {
    auto simple_arena = SimpleArena<1024>{};
    std::cout << " ======== Simple Arena ========\n\n";

    std::cout << "allocated buffer at " << simple_arena._buffer << " ("
              << sizeof simple_arena._buffer << " bytes)\n";

    // Allocate chars
    if (auto* p = simple_arena.create<char>(1))
    {
        *p = 'a';
        std::cout << "allocated a char at " << (void*)p << '\n';
    }

    // Allocate one int
    if (auto* p = simple_arena.create<int>(1))
    {
        *p = 1;
        std::cout << "allocated an int at " << (void*)p << '\n';
    }

    // Allocate chars
    if (auto* p = simple_arena.create<char>(1))
    {
        *p = 'a';
        std::cout << "allocated a char at " << (void*)p << '\n';
    }

    // Allocate chars
    if (auto* p = simple_arena.create<char>(1))
    {
        *p = 'a';
        std::cout << "allocated a char at " << (void*)p << '\n';
    }

    return 0;
}