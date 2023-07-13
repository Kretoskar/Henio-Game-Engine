#pragma once

#include "Output/Public/Screen.h"

namespace Henio
{

    const int SCREEN_WIDTH(1280);
    const int SCREEN_HEIGHT(720);

    class Engine
    {

    public:		
        ~Engine();
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        static Engine& Ref()
        {
            static Engine reference;
            return reference;
        }

        void Quit();
        void Update();
        void Initialize();

        bool ShouldClose() { return screen.ShouldClose(); };
        GLFWwindow& Window() { return *window; }
        float VideoWidth() const { return videoWidth; }
        float VideoHeight() const { return videoHeight; }

    private:
        Engine();
        
        bool run;
        GLFWwindow* window;
        float videoWidth, videoHeight;
        Screen screen;
    };

    static Engine& Core = Engine::Ref();
}
