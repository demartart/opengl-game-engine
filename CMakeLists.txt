cmake_minimum_required(VERSION 3.25)
project(gamework)

set(INDEV ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glfw)
add_subdirectory(assimp)

add_executable(game)
target_sources(game PRIVATE 
    glad/src/glad.c
    src/main.cpp
    src/3d/camera.cpp
    src/3d/mesh.cpp
    src/3d/model.cpp
    src/core/window.cpp
    src/core/buf_counter.cpp
    src/rendering/image.cpp
    src/rendering/shader.cpp
    src/rendering/buffer.cpp
    src/rendering/texture.cpp
    src/rendering/vertex_array.cpp)
target_link_libraries(game PRIVATE glfw assimp)
target_include_directories(game PRIVATE glad/include glm/include stb_image)
if(INDEV)
    target_compile_definitions(game PRIVATE RESPATH="${CMAKE_SOURCE_DIR}/res")
else()
    target_compile_definitions(game PRIVATE RESPATH="./res")
endif()