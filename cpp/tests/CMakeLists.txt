# tests/CMakeLists.txt
enable_testing()

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# Test executable
add_executable(test_core test_core.cpp)

# Link libraries
target_link_libraries(test_core PRIVATE gtest_main core utils)

# Include directories
target_include_directories(test_core PRIVATE ../include)

# Register test
include(GoogleTest)
gtest_discover_tests(test_core)
