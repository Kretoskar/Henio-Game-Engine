#include "Engine.h"

#include <iostream>

namespace Henio
{
    Engine::Engine() : run(true), window(nullptr), videoWidth(SCREEN_WIDTH), videoHeight(SCREEN_HEIGHT)
    {
        glfwInit();
	
        // using 3.3 as it's the doc supported version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if (!screen.Init())
        {
            std::cout << "Failed to create window" << std::endl;
            glfwTerminate();
        }

        // init GLAD
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            glfwTerminate();
        }

        screen.SetParameters();
    }

    Engine::~Engine()
    {
        glfwTerminate();
    }

    void Engine::Initialize()
    {

    }

    void Engine::Update()
    {
        screen.Update();
        screen.NewFrame();
    }

    void Engine::Quit()
    {
        run = false;
    }
}
