#include <benchmark/benchmark.h>
#include <vector>

#include <allocator.hpp>
#include <memory_resource>
#include <ranges>
#include <simple_arena.hpp>

static void BM_SimpleArena(benchmark::State &state) {
    const auto num_values = static_cast<int>(state.range(0));// number of elements
    for (auto _: state) {
        using Arena = SimpleArena<1024 * 1024>;

        auto arena = Arena{};
        const auto allocator = Allocator<int, Arena>(arena);
        auto values = std::vector<int, Allocator<int, Arena>>{allocator};
        for (int i = 0; i < num_values; ++i) { values.push_back(i); }

        // Prevent compiler optimizations from removing the code
        benchmark::DoNotOptimize(values);
    }
}

static void BM_MonotonicBufferResource(benchmark::State &state) {
    const auto num_values = static_cast<int>(state.range(0));// number of elements
    for (auto _: state) {
        auto buffer = std::array<std::byte, 1024 * 1024>{};
        auto mbr = std::pmr::monotonic_buffer_resource{buffer.data(), buffer.size()};
        auto allocator = std::pmr::polymorphic_allocator{&mbr};

        auto values = std::pmr::vector<int>{allocator};
        for (int i = 0; i < num_values; ++i) { values.push_back(i); }

        // Prevent compiler optimizations from removing the code
        benchmark::DoNotOptimize(values);
    }
}

static void BM_NoArena(benchmark::State &state) {
    const auto num_values = static_cast<int>(state.range(0));// number of elements
    for (auto _: state) {
        auto values = std::vector<int>{};
        values.shrink_to_fit();// Forces capacity() == size() == 0
        for (int i = 0; i < num_values; ++i) { values.push_back(i); }

        // Prevent compiler optimizations from removing the code
        benchmark::DoNotOptimize(values);
    }
}

BENCHMARK(BM_SimpleArena)->Arg(100)->Arg(1'000)->Arg(10'000);
BENCHMARK(BM_NoArena)->Arg(100)->Arg(1'000)->Arg(10'000);
BENCHMARK(BM_MonotonicBufferResource)->Arg(100)->Arg(1'000)->Arg(10'000);

BENCHMARK_MAIN();