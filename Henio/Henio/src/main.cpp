#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <glm/glm.hpp>
#include <stb/stb_image.h>

#include "Core/Public/Logger.h"
#include "Core/Public/Window.h"

int main()
{
	
	std::unique_ptr<Window> w = std::make_unique<Window>();
	if (!w->Init(640, 480, "Henio Game Engine"))
	{
		LOG_ERROR("Window init error")
		return -1;
	}
	
	w->MainLoop();
	w->Cleanup();
	
	return 0;
}
