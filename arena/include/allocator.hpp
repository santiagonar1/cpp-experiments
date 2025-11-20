#ifndef CPP_EXPERIMENTS_ALLOCATOR_HPP
#define CPP_EXPERIMENTS_ALLOCATOR_HPP

#include "simple_arena.hpp"

template<typename T>
concept Arena = requires(T arena, std::size_t n) {
    { arena.template create<T>(n) } -> std::same_as<T *>;
};

template<typename T, Arena A = SimpleArena<1024>>
class Allocator {
public:
    using value_type = T;

    explicit Allocator(A &arena) noexcept;

    template<typename U, Arena OA>
    explicit Allocator(const Allocator<U, OA> &other) noexcept;

    auto allocate(std::size_t n) -> T *;

    static auto deallocate(T *p, std::size_t n) noexcept -> void;

    template<typename U, Arena OA>
    friend class Allocator;

private:
    A &_arena;
};

template<typename T, Arena A>
Allocator<T, A>::Allocator(A &arena) noexcept : _arena{arena} {}

template<typename T, Arena A>
template<typename U, Arena OA>
Allocator<T, A>::Allocator(const Allocator<U, OA> &other) noexcept : _arena{other._arena} {}

template<typename T, Arena A>
auto Allocator<T, A>::allocate(std::size_t n) -> T * {
    return _arena.template create<T>(n);
}

template<typename T, Arena A>
auto Allocator<T, A>::deallocate(T *p, std::size_t n) noexcept -> void {}

template<typename T, Arena A>
auto operator==(const Allocator<T, A> &lhs, const Allocator<T, A> &rhs) noexcept -> bool {
    return &lhs._arena == &rhs._arena;
}

template<typename T, Arena A>
auto operator!=(const Allocator<T, A> &lhs, const Allocator<T, A> &rhs) noexcept -> bool {
    return !(lhs == rhs);
}


#endif//CPP_EXPERIMENTS_ALLOCATOR_HPP
