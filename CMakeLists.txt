cmake_minimum_required(VERSION 3.28)
project(TRANSGATOR LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# -----------------------------
# Fetch SFML 3 from GitHub
# -----------------------------
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

# -----------------------------
# Project sources
# -----------------------------
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)

# -----------------------------
# Executable
# -----------------------------
add_executable(TRANSGATOR ${PROJECT_SOURCES})

# -----------------------------
# Link SFML 3 libraries
# -----------------------------
# SFML 3 now splits graphics, window, system properly
target_link_libraries(TRANSGATOR
        PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)

# Ensure your build uses the FetchContent version
target_include_directories(TRANSGATOR PRIVATE ${sfml_SOURCE_DIR}/include)

# Optional: set startup project for Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TRANSGATOR)