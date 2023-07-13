#include "Timer.h"

#include <GLFW/glfw3.h>

namespace Henio {

    T_Timer::T_Timer() : deltaTime(0.0f), lastFrame(0.0f)
    {

    }

    T_Timer::~T_Timer()
    {

    }

    void T_Timer::Initialize()
    {

    }

    void T_Timer::Tick()
    {
        deltaTime = glfwGetTime() - lastFrame;
        lastFrame = glfwGetTime();
    }
}
