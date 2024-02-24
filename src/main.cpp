#include "core/window.hpp"
#include "core/buf_counter.hpp"
#include "rendering/shader.hpp"
#include "rendering/vertex_array.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>
#include <vector>

bool firstMouse = true;
float lastPosX = 0.0f, lastPosY = 0.0f;
float cameraYaw = -90.0f;
float cameraPitch = 0.0f;

glm::mat4 nextView = glm::mat4 { 1.0f };

void processMouse(GLFWwindow *window, double mx, double my) {
    if (firstMouse) {
        lastPosX = mx;
        lastPosY = my;
        firstMouse = false;
    }

    float xOff = mx - lastPosX;
    float yOff = lastPosY - my;

    lastPosX = mx;
    lastPosY = my;

    float sens = 0.05f;
    cameraYaw += xOff * sens;
    cameraPitch += yOff * sens;

    if (cameraPitch > 89.0f) {
        cameraPitch = 89.0f;
    }
    if (cameraPitch < -89.0f) {
        cameraPitch = -89.0f;
    }

    cameraYaw = glm::mod(cameraYaw, 360.f);

    glm::vec3 forward = glm::normalize(glm::vec3 {
        cosf(glm::radians(cameraYaw)) * cosf(glm::radians(cameraPitch)),
        sinf(glm::radians(cameraPitch)),
        sinf(glm::radians(cameraYaw)) * cosf(glm::radians(cameraPitch))
    });
    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3 { 0.0f, 1.0f, 0.0f }));
    glm::vec3 up = glm::normalize(glm::cross(right, forward));
    nextView = glm::lookAt(
        glm::vec3 { 0.0f, 0.0f, 3.0f }, 
        glm::vec3 { 0.0f, 0.0f, 3.0f } + forward,
        up
    );
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

    glm::mat4 model = glm::mat4 { 1.0f };
    model = glm::translate(model, glm::vec3 { 0.0f, 0.0f, 0.0f });

    glm::mat4 view = glm::mat4 { 1.0f };
    view = glm::lookAt(
        glm::vec3 { 0.0f, 0.0f, 3.0f },
        glm::vec3 { 0.0f, 0.0f, 0.0f },
        glm::vec3 { 0.0f, 1.0f, 0.0f }
    );

    glm::mat4 projection = glm::mat4 { 1.0f };
    projection = glm::perspective(glm::radians(85.0f), (float)window.width / window.height, 0.1f, 100.0f);

    shader.UniformSetmat4("model", model);
    shader.UniformSetmat4("view", view);
    shader.UniformSetmat4("projection", projection);

    float dt = 0.0f;
    float lastFrame = 0.0f;

    glfwSetCursorPosCallback(window.windowHandle, processMouse);
    glfwSetInputMode(window.windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    while (window.IsOpen()) {
        float currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.5f, 0.0f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.UniformSetmat4("view", nextView);
        
        DrawVAO(vao);

        window.SwapBuffers();
    }

    BufCounter::CleanUp();
    window.Destroy();
    return 0;
}