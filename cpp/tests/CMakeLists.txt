cmake_minimum_required(VERSION 3.20)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(test_core test_core.cpp)

target_link_libraries(test_core
    PRIVATE
        GTest::gtest_main
        AtlasCore         # <- your C++ library from src/
)

include(GoogleTest)
gtest_discover_tests(test_core)
