cmake_minimum_required(VERSION 4.0)
project(cpp_experiments)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

# Set compiler to use Xcode SDK
if (APPLE)
    execute_process(
            COMMAND xcrun --show-sdk-path
            OUTPUT_VARIABLE SDKROOT
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(CMAKE_OSX_SYSROOT "${SDKROOT}" CACHE PATH "macOS SDK path" FORCE)
endif ()

set(LIBRARY_NAME "arenas")
set(EXECUTABLE_NAME ${LIBRARY_NAME}.out)

set(SOURCES
        src/simple_arena.cpp
)

add_library(${LIBRARY_NAME}
        ${SOURCES}
)

target_include_directories(${LIBRARY_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(${LIBRARY_NAME}
        PUBLIC cxx_std_23
)

add_executable(${EXECUTABLE_NAME}
        main.cpp
)

target_link_libraries(${EXECUTABLE_NAME}
        PRIVATE ${LIBRARY_NAME}
)

enable_testing()
add_subdirectory(tests)


