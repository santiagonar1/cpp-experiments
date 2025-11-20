#include "object_arena.hpp"

ObjectArena::ObjectArena(const std::size_t capacity)
    : _capacity{capacity}, _buffer{new std::byte[capacity]}, _ptr{_buffer} {}

ObjectArena::~ObjectArena() {
    call_destructors();
    delete[] _buffer;
}

auto ObjectArena::call_destructors() noexcept -> void {
    while (_destruct_tail) {
        _destruct_tail->destructor(_destruct_tail->object);
        _destruct_tail = _destruct_tail->prev;
    }
}
