#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <windows.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "Rendering/Public/Shader.h"
#include "Input/Public/Keyboard.h"
#include "Input/Public/Mouse.h"
#include "Input/Public/Gamepad.h"
#include "Components/Public/Camera.h"
#include "ECS/Base/BaseComponent.h"
#include "ECS/Base/EntityManager.h"
#include "ECS/Base/Types.h"
#include "Engine/Engine.h"
#include "Events/Events.h"
#include "Output/Public/Screen.h"
#include "Rendering/Public/Texture.h"
#include "Rendering/Models/Public/Cube.hpp"
#include "Rendering/Models/Public/Lamp.hpp"
#include "Timer/Timer.h"

void processInput(double deltaTime);

Gamepad mainGamepad(0);

uint16_t SCR_WIDTH = 800;
uint16_t SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Screen screen;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

class TestComp1 : public ECS::BaseComponent
{
	
};

int main()
{
	ECS::EntityManager manager;
	auto id = manager.AddNewEntity();
	auto id1 = manager.AddNewEntity();
	std::cout << id << " " << id1 << std::endl;

	manager.DestroyEntity(id1);
	auto id2 = manager.AddNewEntity();

	
	auto typeID1 = ECS::CompType<TestComp1>();
	std::cout << id << " " << id2 << " " << typeID1;
	
	Henio::Core.Initialize();
	Henio::Timer.Initialize();
	Henio::Event.Initialiaze();

	while (!Henio::Core.ShouldClose())
	{
		Henio::Timer.Tick();
		Henio::Event.Poll();
		Henio::Core.Update();
	}

	return 0;
	
	
	// --------------------
	
	Shader shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");

	Model model(glm::vec3(0, 0, -5), glm::vec3(0.05f));
	model.LoadModel("assets/models/monke/scene.gltf");

	SpotLight spotLight =
		{
			camera.cameraPos, camera.cameraFront, 1.0f, 0.07f, 0.032f,
			glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(20.0f)),
			glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(1.0f)
		};

	DirLight dirLight = {glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.1f), glm::vec3(0.4f), glm::vec3(0.5f)};
	
	mainGamepad.Update();
	if (mainGamepad.IsPresent())
	{
		std::cout << mainGamepad.GetName() << " is present." << std::endl;
	}
	else
	{
		std::cout << "Gamepad not present" << std::endl;
	}

	long long startTimeMillis = GetTickCount();
	
	while (!screen.ShouldClose())
	{
		const double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;
		processInput(deltaTime);

		long long currentTimeMillis = GetTickCount();
		//TODO: change to currenttime?
		float animTimeSec = static_cast<float>(currentTimeMillis - startTimeMillis) / 1000.0f;
		
		screen.Update();
		
		shader.Activate();
		shader.Set3Float("viewPos", camera.cameraPos);

		dirLight.Render(shader);
		
		shader.SetInt("nPointLights", 0);
		
		spotLight.position = camera.cameraPos;
		spotLight.direction = camera.cameraFront;
		spotLight.Render(0, shader);
		shader.SetInt("nSpotLights", 1);

		const glm::mat4 view = camera.GetViewMatrix();
		const glm::mat4 projection = glm::perspective(glm::radians(camera.GetFov()), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);

		std::vector<glm::mat4> transforms;
		
		model.GetBoneTransforms(animTimeSec, transforms);
		
		for (uint32_t i = 0; i < transforms.size(); i++)
		{
			glUniformMatrix4fv(glGetUniformLocation(shader.id, "bones"), (GLsizei)transforms.size(), GL_FALSE, glm::value_ptr(transforms[0]));
		}
		
		model.Render(shader);
		
		screen.NewFrame();
	}

	model.Cleanup();
	
	glfwTerminate();
	return 0;
}

void processInput(double deltaTime)
{
	if (Keyboard::Key(GLFW_KEY_ESCAPE))
	{
		screen.SetShouldClose(true);
	}

	// move camera
	if (Keyboard::Key(GLFW_KEY_W))
	{
		camera.UpdateCameraPosition(CameraDirection::FORWARD, deltaTime);
	}

	if (Keyboard::Key(GLFW_KEY_S))
	{
		camera.UpdateCameraPosition(CameraDirection::BACKWARD, deltaTime);
	}

	if (Keyboard::Key(GLFW_KEY_A))
	{
		camera.UpdateCameraPosition(CameraDirection::LEFT, deltaTime);
	}

	if (Keyboard::Key(GLFW_KEY_D))
	{
		camera.UpdateCameraPosition(CameraDirection::RIGHT, deltaTime);
	}

	if (Keyboard::Key(GLFW_KEY_SPACE))
	{
		camera.UpdateCameraPosition(CameraDirection::UP, deltaTime);
	}

	if (Keyboard::Key(GLFW_KEY_LEFT_SHIFT))
	{
		camera.UpdateCameraPosition(CameraDirection::DOWN, deltaTime);
	}

	double dx = Mouse::GetMouseDeltaX() / 50;
	double dy = Mouse::GetMouseDeltaY() / 50;

	if (glm::abs(dx) > glm::epsilon<double>() || glm::abs(dy) > glm::epsilon<double>())
	{
		camera.UpdateCameraDirection(dx, dy);
	}

	double scrollDy = Mouse::GetScrollDeltaY();
	if (glm::abs(scrollDy) > glm::epsilon<double>())
	{
		camera.UpdateCameraFov(scrollDy);
	}
}