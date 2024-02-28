#include "conf.hpp"
#include "3d/camera.hpp"
#include "core/window.hpp"
#include "core/buf_counter.hpp"
#include "rendering/shader.hpp"
#include "rendering/vertex.hpp"
#include "rendering/vertex_array.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>
#include <vector>

/*
 * TODO for texture loading
 *  - Frag shader accepts uniform
 *  - Vertices specify a texture coordinate
 *  - Need a sample texture image for testing
*/

bool firstMouse = true;
f32 lastPosX = 0.0f, lastPosY = 0.0f;

Camera mainCamera;

void processMouse(GLFWwindow *window, f64 mx, f64 my) {
    if (firstMouse) {
        lastPosX = mx;
        lastPosY = my;
        firstMouse = false;
    }

    f32 xOff = mx - lastPosX;
    f32 yOff = lastPosY - my;

    lastPosX = mx;
    lastPosY = my;

    mainCamera.ProcessMouse(glm::vec2 { xOff, yOff });
}

void processKeyboard(GLFWwindow *window, float dt) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    
    glm::vec2 dir = glm::vec2 { 0.0f };
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        dir.y = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        dir.y = -1;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        dir.x = -1;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        dir.x = 1;
    }
    if (dir != glm::vec2 { 0.0f, 0.0f })
        dir = glm::normalize(dir);
    mainCamera.ProcessInput(dir, dt);
}

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
    
    mainCamera = Camera::Create(glm::vec3 { 0.0f, 0.0f, 3.0f });

    std::vector<Vertex> verts = {
        { -0.5f, -0.5f, 0.0f },
        {  0.5f, -0.5f, 0.0f },
        { -0.5f,  0.5f, 0.0f },
        {  0.5f,  0.5f, 0.0f },
    };
    std::vector<u32> indices = {
        0, 1, 2,
        2, 1, 3,
    }; 

    VertexArray vao = GenerateVAO(verts.data(), verts.size(), indices.data(), indices.size());

    glm::mat4 model = glm::mat4 { 1.0f };
    model = glm::translate(model, glm::vec3 { 0.0f, 0.0f, 0.0f });

    glm::mat4 view = glm::mat4 { 1.0f };
    view = mainCamera.GetViewMatrix();

    glm::mat4 projection = glm::mat4 { 1.0f };
    projection = glm::perspective(glm::radians(85.0f), (f32)window.width / window.height, 0.1f, 100.0f);

    shader.UniformSetmat4("model", model);
    shader.UniformSetmat4("view", view);
    shader.UniformSetmat4("projection", projection);

    f32 dt = 0.0f;
    f32 lastFrame = 0.0f;

    glfwSetCursorPosCallback(window.windowHandle, processMouse);
    glfwSetInputMode(window.windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    while (window.IsOpen()) {
        f32 currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        processKeyboard(window.windowHandle, dt);

        glClearColor(0.5f, 0.0f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.UniformSetmat4("view", mainCamera.GetViewMatrix());
        
        DrawVAO(vao);

        window.SwapBuffers();
    }

    BufCounter::CleanUp();
    window.Destroy();
    return 0;
}
