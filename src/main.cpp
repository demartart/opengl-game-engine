#include "core/window.hpp"
#include "core/buf_counter.hpp"
#include "rendering/shader.hpp"
#include "rendering/vertex_array.hpp"

#include <glad/glad.h>

#include <cstdio>
#include <vector>


int main() {
    auto result = Window::Create(1280, 720, "Hello, World");
    if (!result.has_value()) {
        fprintf(stderr, "Failed to Create Window\n");
        return 1;
    }
    Window window = result.value();

    if (!window.InitOpenGL()) {
        fprintf(stderr, "Failed to Initialize OpenGL\n");
        return 2;
    }

    Shader shader = Shader::Create("default.fs", "default.vs");
    shader.Activate();

    std::vector<float> verts = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
    };
    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 1, 3,
    };

    VertexArray vao = GenerateVAO(verts.data(), verts.size(), indices.data(), indices.size());

    while (window.IsOpen()) {
        glClearColor(0.5f, 0.0f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        DrawVAO(vao);

        window.SwapBuffers();
    }

    BufCounter::CleanUp();
    window.Destroy();
    return 0;
}