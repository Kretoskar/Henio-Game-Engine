#include "Events.h"
#include "Engine/Engine.h"

namespace Henio {

    // callback function definition
    void WindowCloseCallback(GLFWwindow* window);

    Events::Events() { }

    Events::~Events() { }

    void Events::Poll()
    {
        glfwPollEvents();
    }

    void Events::Initialiaze()
    {
        //GLFWwindow& window = Core.Window();
       // glfwSetWindowCloseCallback(&window, WindowCloseCallback);
    }

    void WindowCloseCallback(GLFWwindow* window)
    {		
        Henio::Core.Quit();
    }
}
