cmake_minimum_required(VERSION 3.16)
project(utag LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_compile_options(
    -std=c++17
    # -pipe
    # -Wall
    # -Wextra
    # -Werror
    # -Wpedantic
)

add_subdirectory(taglib)
add_subdirectory(app)
