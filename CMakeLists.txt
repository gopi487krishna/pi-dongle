cmake_minimum_required(VERSION 3.16)
project(pi-dongle)

# C++17 is enough for this project
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_definitions( -DSOURCE_DIR="${CMAKE_SOURCE_DIR}" )

include_directories(${PROJECT_SOURCE_DIR}/include)


enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(executable)
