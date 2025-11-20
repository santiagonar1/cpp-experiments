# Arena and Allocator implementations

In this folder I showcase a simple implementation of two arenas, as well as a custom allocator. We have:

- **SimpleArena**: a simple arena that uses a single block of memory.
- **ObjectArena**: an arena that showcases how to store destructors of objects.
- **Allocator**: an allocator to be used with the Simple Arena.

I have also included the corresponding [test](tests) and [benchmark](benchmarks) folders.

## Useful links

- [Blog post about ObjectArena](https://medium.com/@sgn00/high-performance-memory-management-arena-allocators-c685c81ee338)
- [Simple arena implementation and std::align](https://lesleylai.info/en/std-align/)
- [Monotonic Buffer Resource](https://en.cppreference.com/w/cpp/memory/monotonic_buffer_resource.html)
- [Allocator reference](https://en.cppreference.com/w/cpp/named_req/Allocator.html)
- [std::align](https://en.cppreference.com/w/cpp/memory/align.html)