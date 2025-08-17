cmake_minimum_required(VERSION 3.15)
project(BlockBreaker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find raylib via pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED raylib)

# Add executable
add_executable(Snake main.cpp)

# Include raylib headers
target_include_directories(Snake  PRIVATE ${RAYLIB_INCLUDE_DIRS})

# Link raylib and dependencies
target_link_libraries(Snake PRIVATE ${RAYLIB_LIBRARIES})
