cmake_minimum_required(VERSION 3.10)
project(object_scanner_module)

# Download & include Pybind11 automatically
include(FetchContent)
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.11.1  # Use latest stable version
)
FetchContent_MakeAvailable(pybind11)

# Create Python module
add_library(object_scanner MODULE src/ObjectScanner.cpp)
target_link_libraries(object_scanner PRIVATE pybind11::module)

# Ensure correct output name
set_target_properties(object_scanner PROPERTIES PREFIX "" SUFFIX ".so")
