# Use Homebrew LLVM toolchain consistently (compiler + archiver + ranlib).
set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang" CACHE FILEPATH "" FORCE)
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++" CACHE FILEPATH "" FORCE)

set(CMAKE_AR "/opt/homebrew/opt/llvm/bin/llvm-ar" CACHE FILEPATH "" FORCE)
set(CMAKE_RANLIB "/opt/homebrew/opt/llvm/bin/llvm-ranlib" CACHE FILEPATH "" FORCE)

# Optional: ensure the target arch is consistent with your link line.
set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "" FORCE)
