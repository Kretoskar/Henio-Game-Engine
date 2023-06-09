﻿#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Screen
{
public:
    static uint16_t SCR_WIDTH;
    static uint16_t SCR_HEIGHT;
    static const char* APP_NAME;

    static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

    Screen();

    bool Init();

    void SetParameters();

    void Update();
    void NewFrame();

    bool ShouldClose();
    void SetShouldClose(bool shouldClose);

private:
    GLFWwindow* window;
};
