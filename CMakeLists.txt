cmake_minimum_required(VERSION 3.15)
project(ROSE)

set(CMAKE_CXX_STANDARD 17)

# Add configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# Define directories for includes and libraries
include_directories(vendor/openal/include)
include_directories(vendor/libsndfile/include)
include_directories(C:/tools/vcpkg/installed/x64-windows/include/SDL2)

link_directories(vendor/openal/build)
link_directories(vendor/libsndfile/build)
link_directories(C:/tools/vcpkg/installed/x64-windows/lib)

# Add subdirectories for your projects
add_subdirectory(ROSE)
add_subdirectory(Example)
add_subdirectory(vendor/openal)
add_subdirectory(vendor/libsndfile)
