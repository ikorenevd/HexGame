#include <iostream>
#include <memory>

#include <Engine/Engine.hpp>

int main()
{
	std::shared_ptr<Window> window;

	window = std::make_shared<Window>("HexGame", glm::ivec2(1920, 1080));

	window->create();

	bool running = false;

	running = true;
	while (running)
	{
		window->pollEvents();

		if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_F4))
		{
			running = false;
		}

		window->display();
	}

	return 0;
}
