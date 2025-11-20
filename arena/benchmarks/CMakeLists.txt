find_package(benchmark REQUIRED)

function(compile_benchmark benchmark_name)
    add_executable(${benchmark_name} ${ARGN})
    target_link_libraries(${benchmark_name}
            PRIVATE ${LIBRARY_NAME}
            PRIVATE benchmark::benchmark
    )
endfunction()

set(SOURCES
        arena_benchmark.cpp
)

compile_benchmark(${LIBRARY_NAME}_benchmarks
        ${SOURCES}
)
