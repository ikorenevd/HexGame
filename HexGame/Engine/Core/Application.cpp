#include <iostream>

#include <Engine/Core/Application.hpp>

#include <Engine/Core/Window.hpp>
#include <Engine/Core/Layer.hpp>

Application::Application(const std::string& name, const glm::ivec2& windowSize) :
	window(std::make_shared<Window>(name, windowSize)),
	name(name),
	running(false)
{
}

void Application::update()
{
	for (Layer* layer : layers)
	{
		layer->update();
	}

	if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_F4))
	{
		running = false;
	}
}

void Application::render()
{
	for (Layer* layer : layers)
	{
		layer->render();
	}
}

void Application::run()
{
	running = true;

	glfwInit();

	window->create();

	glewExperimental = true;
	glewInit();

	pushingLayers();

#define UPSCount 60

	double upsTime = 1.f / UPSCount;

	double lastTime = glfwGetTime();
	double timer = lastTime;

	double deltaTime = 0;
	double nowTime = 0;

	int frames = 0;
	int updates = 0;

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(.85, .85, .8, 1);

	while (running)
	{
		nowTime = glfwGetTime();
		deltaTime += (nowTime - lastTime) / upsTime;
		lastTime = nowTime;

		while (deltaTime >= 1.f)
		{
			window->pollEvents();
			update();
			updates++;
			deltaTime--;
		}

		glClear(GL_COLOR_BUFFER_BIT);
		render();
		frames++;
		window->display();

		if (glfwGetTime() - timer > 1.f)
		{
			timer++;
			std::clog << "UPS/FPS: " << updates << "/" << frames << std::endl;
			updates = 0;
			frames = 0;
		}
	}
}

void Application::pushLayer(Layer* value)
{
	layers.push_back(value);
	value->onAttach();
}

const std::string& Application::getName() const
{
	return name;
}

const std::shared_ptr<Window>& Application::getWindow() const
{
	return window;
}

