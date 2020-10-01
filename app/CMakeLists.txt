cmake_minimum_required(VERSION 3.1)

project(app_project LANGUAGES CXX)
set(SOURCE_EXE main.cpp)
add_subdirectory(src)

add_compile_options(
        -std=c++17
        # -Werror
        # -Wall
        # -Wextra
        # -Wpedantic
        # -Wno-unused-parameter
)


add_executable(utag ${SOURCE_EXE})

target_link_libraries(utag ${CMAKE_SOURCE_DIR}/build/taglib/libtag.a)
target_link_libraries(utag utaglib)
set_target_properties(utag PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../)