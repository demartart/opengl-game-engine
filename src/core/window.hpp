#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <optional>

class Window {
public:
    GLFWwindow *windowHandle;
    int width, height;

    static std::optional<Window> Create(int width, int height, const char *title);
    void Destroy();

    void Close();
    bool IsOpen();
    
    bool InitOpenGL();
    void SwapBuffers();
};

#endif