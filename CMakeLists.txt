cmake_minimum_required(VERSION 3.20)
project(AtlasQuantEngine LANGUAGES CXX)

# ----------------------------
#  General Compiler Settings
# ----------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build options
option(ATLAS_ENABLE_TESTS "Enable unit tests" ON)
option(ATLAS_ENABLE_WARNINGS "Enable compiler warnings" ON)

# ----------------------------
#  Optimized Build Flags
# ----------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(
        -O3 -march=native -mtune=native
        -ffast-math
        -fno-plt
    )
endif()

# ----------------------------
#  Enable Warnings
# ----------------------------
if(ATLAS_ENABLE_WARNINGS)
    add_compile_options(
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion
        -Wno-unused-variable -Wno-unused-parameter
    )
endif()

# ----------------------------
#  Clang-Tidy Support
# ----------------------------
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()

# ----------------------------
#  Source Structure
# ----------------------------
add_subdirectory(src)

# ----------------------------
#  Unit Tests
# ----------------------------
if(ATLAS_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
