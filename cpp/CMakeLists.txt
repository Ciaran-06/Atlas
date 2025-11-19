cmake_minimum_required(VERSION 3.20)
project(AtlasCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------- Libraries --------

# Utils library
add_library(utils
    src/Statistics.cpp
    src/FileLoader.cpp
)
target_include_directories(utils PUBLIC include)

# Core library (Engine logic)
add_library(core
    src/Engine.cpp        # <-- must include Engine.cpp
)
target_include_directories(core PUBLIC include)
target_link_libraries(core PUBLIC utils)

# -------- Executable --------
add_executable(atlas_engine
    src/main.cpp          # only main.cpp here
)
target_link_libraries(atlas_engine PRIVATE core utils ${PROJECT_SOURCE_DIR}/include)

# -------- Testing --------
enable_testing()
add_subdirectory(tests)
