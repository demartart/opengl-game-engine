#include "game.hpp"
#include <cstdio>
#include <cstdlib>

void Game::Init(u32 windowWidth, u32 windowHeight, const std::string &windowTitle) {
    auto result = Window::Create(windowWidth, windowHeight, windowTitle.c_str());
    if (!result.has_value()) {
        fprintf(stderr, "[GLFW] Failed to Create Window\n");
        exit(1);
    }
    this->gameWindow = result.value();

    if (!this->gameWindow.InitOpenGL()) {
        fprintf(stderr, "[OPENGL] Failed to Initialize OpenGL\n");
        exit(2);
    }
}