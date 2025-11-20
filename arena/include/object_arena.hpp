#ifndef CPP_EXPERIMENTS_OBJECT_ARENA_HPP
#define CPP_EXPERIMENTS_OBJECT_ARENA_HPP

#include <functional>
#include <memory>

class ObjectArena {
public:
    explicit ObjectArena(std::size_t capacity);
    ~ObjectArena();

    template<typename T, typename... Args>
    [[nodiscard]] auto create(Args &&...args) -> T *;

private:
    struct DestructNode {
        std::function<void(void *)> destructor;
        void *object;
        DestructNode *prev;
    };

    auto call_destructors() noexcept -> void;

    std::size_t _capacity;
    std::byte *_buffer;
    void *_ptr;
    DestructNode *_destruct_tail{nullptr};
};


template<typename T, typename... Args>
auto ObjectArena::create(Args &&...args) -> T * {
    constexpr int num_elements = 1;
    constexpr auto size = num_elements * sizeof(T);
    auto *aligned_pointer = static_cast<T *>(std::align(alignof(T), size, _ptr, _capacity));

    if (not aligned_pointer) { return nullptr; }

    T *object = new (aligned_pointer) T(std::forward<Args>(args)...);
    _capacity -= size;
    _ptr = reinterpret_cast<std::byte *>(aligned_pointer) + size;

    if constexpr (std::is_trivially_destructible_v<T>) { return object; }

    auto *dtor_aligned_pointer = static_cast<DestructNode *>(
            std::align(alignof(DestructNode), sizeof(DestructNode), _ptr, _capacity));

    if (not dtor_aligned_pointer) { return nullptr; }

    auto destructor_call = [](void *obj) { static_cast<T *>(obj)->~T(); };
    auto *node = new (dtor_aligned_pointer) DestructNode{destructor_call, object, _destruct_tail};
    _destruct_tail = node;
    _capacity -= sizeof(DestructNode);
    _ptr = reinterpret_cast<std::byte *>(dtor_aligned_pointer) + sizeof(DestructNode);
    return object;
}


#endif//CPP_EXPERIMENTS_OBJECT_ARENA_HPP
