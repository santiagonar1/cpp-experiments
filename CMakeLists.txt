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

enable_testing()

add_subdirectory(arena)
