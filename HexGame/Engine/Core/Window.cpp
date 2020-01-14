#include <Engine/Core/Window.hpp>

Window::Window(const std::string& title, const glm::ivec2& size):
	window(nullptr),
	title(title),
	size(size),
	vsync(false)
{
	glfwInit();

	glewExperimental = true;
	glewInit();
}

void Window::create()
{
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(size.x, size.y, title.c_str(), 0, 0);

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);

	{
		const GLFWvidmode* vm = glfwGetVideoMode(glfwGetPrimaryMonitor());

		glfwSetWindowPos(window, (vm->width - size.x) / 2, (vm->height - size.y) / 2);
	}

	setVSync(vsync);

	// TODO: добавить callbackи для инпута
}

void Window::display()
{
	glfwSwapBuffers(window);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

GLFWwindow* Window::getGLFWWindow() const
{
	return window;
}

void Window::setVSync(bool value)
{
	glfwSwapInterval(value ? 1 : 0);

	vsync = value;
}

bool Window::isVSync() const
{
	return vsync;
}

const glm::ivec2& Window::getSize() const
{
	return size;
}
