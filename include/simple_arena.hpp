#ifndef CPP_EXPERIMENTS_SIMPLE_ARENA_HPP
#define CPP_EXPERIMENTS_SIMPLE_ARENA_HPP

#include <memory>
#include <type_traits>

template<typename T>
concept TriviallyDestructible = std::is_trivially_destructible_v<T>;

template<std::size_t N>
class SimpleArena {
public:
    template<TriviallyDestructible T>
    [[nodiscard]] auto create(std::size_t num_elements) noexcept -> T *;

    std::byte _buffer[N]{};

private:
    std::size_t _capacity{N};
    void *_ptr{_buffer};
};

template<std::size_t N>
template<TriviallyDestructible T>
auto SimpleArena<N>::create(std::size_t num_elements) noexcept -> T * {
    const auto size = num_elements * sizeof(T);
    if (std::align(alignof(T), size, _ptr, _capacity)) {
        // After calling align, _ptr points to the first element of the (aligned) region allocated
        auto *result = static_cast<T *>(_ptr);
        // std::align moved _ptr to a position where it is aligned based on T. Now we need to move
        // it to the next available position based on the number of elements allocated
        _ptr = reinterpret_cast<std::byte *>(result) + size;
        // std::align already reduced the _capacity based on the alignment, but now we have to
        // consider the number of elements allocated
        _capacity -= size;
        return result;
    }

    return nullptr;
}


#endif//CPP_EXPERIMENTS_SIMPLE_ARENA_HPP
