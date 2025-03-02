cmake_minimum_required(VERSION 3.10)
project(memory_pool_module)

# Download & include Pybind11 automatically
include(FetchContent)
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.11.1  # Use latest stable version
)
FetchContent_MakeAvailable(pybind11)

# Create Python module
add_library(memory_pool MODULE src/MemoryPool.cpp src/MemoryPool.cpp)
target_link_libraries(memory_pool PRIVATE pybind11::module)

# Ensure correct output name
set_target_properties(memory_pool PROPERTIES PREFIX "" SUFFIX ".so")
