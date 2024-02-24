cmake_minimum_required(VERSION 3.25)
project(gamework)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glfw)

add_executable(game)
target_sources(game PRIVATE 
    glad/src/glad.c
    src/main.cpp
    src/core/window.cpp
    src/core/buf_counter.cpp
    src/rendering/shader.cpp
    src/rendering/buffer.cpp
    src/rendering/vertex_array.cpp)
target_link_libraries(game PRIVATE glfw)
target_include_directories(game PRIVATE glad/include)