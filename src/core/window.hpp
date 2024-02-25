#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../conf.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <optional>

class Window {
public:
    GLFWwindow *windowHandle;
    i32 width, height;

    static std::optional<Window> Create(i32 width, i32 height, const char *title);
    void Destroy();

    void Close();
    bool IsOpen();
    
    bool InitOpenGL();
    void SwapBuffers();
};

#endif