#ifndef GAME_HPP__
#define GAME_HPP__

#include "../conf.hpp"
#include "../core/window.hpp"
#include <string>

class Game {
public:
    Window gameWindow;

    f32 deltaTime;

    void Init(u32 windowWidth, u32 windowHeight, const std::string &windowTitle);
    bool IsRunning();

    virtual void Start();
    virtual void Tick(f32 dt);

private:
    f32 lastFrame;
};

#endif