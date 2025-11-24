cmake_minimum_required(VERSION 3.20)
project(AtlasCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- DuckDB include + library ---
# Headers in your project
set(DUCKDB_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/duckdb")

# Set this to the actual path of libduckdb.dylib on your system
set(DUCKDB_LIBRARY "${PROJECT_SOURCE_DIR}/include/duckdb/include/libduckdb.dylib")

include_directories(${DUCKDB_INCLUDE_DIR})

# --- Utils ---
add_library(utils
    src/Statistics.cpp
)
target_include_directories(utils PUBLIC include)

# --- Core ---
add_library(core
    src/Engine.cpp
    src/duckdb_loader.cpp
)

target_include_directories(core PUBLIC include)
target_link_libraries(core PUBLIC utils ${DUCKDB_LIBRARY})

# --- Executable ---
add_executable(atlas_engine src/main.cpp)
target_link_libraries(atlas_engine PRIVATE core utils)

# --- Tests ---
enable_testing()
add_subdirectory(tests)