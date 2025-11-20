set(LIBRARY_NAME "arenas")
set(EXECUTABLE_NAME ${LIBRARY_NAME}.out)

set(SOURCES
        src/simple_arena.cpp
        src/object_arena.cpp
)

add_library(${LIBRARY_NAME}
        ${SOURCES}
)

target_include_directories(${LIBRARY_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(${LIBRARY_NAME}
        PUBLIC cxx_std_23
)

add_subdirectory(tests)
add_subdirectory(benchmarks)
add_subdirectory(apps)
