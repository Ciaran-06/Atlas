# ...existing code...
cmake_minimum_required(VERSION 3.20)
project(AtlasCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- DuckDB include + optional library ---
set(DUCKDB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/duckdb" CACHE PATH "Path to DuckDB headers (duckdb.hpp)")
set(DUCKDB_LIBRARY "" CACHE PATH "Optional: path to libduckdb (.so/.a/.lib)")

# --- Arrow include + optional library ---
find_package(Arrow REQUIRED)

message(STATUS "DuckDB include dir: ${DUCKDB_INCLUDE_DIR}")

# --- Utils ---
add_library(utils
    src/Statistics.cpp
    include/duckdb/duckdb.cpp
)
# ensure project headers and duckdb headers are visible when building utils
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${DUCKDB_INCLUDE_DIR})

# --- Core ---
add_library(core
    src/Engine.cpp
    src/duckdb_loader.cpp
)
# ensure core can see the same headers
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${DUCKDB_INCLUDE_DIR})
target_link_libraries(core PUBLIC utils ${DUCKDB_LIBRARY})

# --- Executable ---
add_executable(atlas_engine src/main.cpp)
target_include_directories(atlas_engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${DUCKDB_INCLUDE_DIR})
target_link_libraries(atlas_engine PRIVATE core utils Arrow::arrow_shared)

# --- Tests ---
enable_testing()
add_subdirectory(tests)
# ...existing code...