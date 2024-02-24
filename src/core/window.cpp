#include "window.hpp"

#include <glad/glad.h>

std::optional<Window> Window::Create(int width, int height, const char *title) {
    Window w = {
        .windowHandle = nullptr,
        .width = width,
        .height = height,
    };

    if (!glfwInit()) {
        return std::nullopt;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    w.windowHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!w.windowHandle) {
        return std::nullopt;
    }

    glfwMakeContextCurrent(w.windowHandle);
    return w;
}

void Window::Destroy() {
    glfwDestroyWindow(windowHandle);
    glfwTerminate();
}

void Window::Close() {
    glfwSetWindowShouldClose(windowHandle, true);
}

bool Window::IsOpen() {
    glfwPollEvents();
    return !glfwWindowShouldClose(windowHandle);
}

bool Window::InitOpenGL() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        return false;
    }

    glViewport(0, 0, width, height);
    return true;
}

void Window::SwapBuffers() {
    glfwSwapBuffers(windowHandle);
}