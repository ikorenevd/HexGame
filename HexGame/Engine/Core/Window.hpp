#pragma once

#include <string>

#include <Engine/Core/OpenGL.hpp>

class Window
{
public:
	Window(const std::string& title = std::string("Window"), const glm::ivec2& size = glm::ivec2(1280, 720));

	void create();
	
	void display(); // glfwSwapBuffers()

	void pollEvents();

	GLFWwindow* getGLFWWindow() const;

	void setVSync(bool value);
	bool isVSync() const;

	const glm::ivec2& getSize() const;
private:
	GLFWwindow* window;

	std::string title;

	glm::ivec2 size;

	bool vsync;
};
