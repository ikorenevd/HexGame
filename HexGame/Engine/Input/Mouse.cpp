#include <Engine/Input/Mouse.hpp>

glm::vec2 Mouse::coordinates = glm::vec2(0.f);

bool Mouse::buttonStates[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::pressedButtons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::releasedButtons[GLFW_MOUSE_BUTTON_LAST] = { 0 };

void Mouse::posCallback(GLFWwindow* window, double _x, double _y)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	coordinates.x = (float)_x;
	coordinates.y = (float)(height - _y);
}

void Mouse::btnCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button < 0)
		return;

	if (action != GLFW_RELEASE && buttonStates[button] == false)
	{
		pressedButtons[button] = true;
		releasedButtons[button] = false;
	}

	if (action == GLFW_RELEASE && buttonStates[button] == true)
	{
		pressedButtons[button] = false;
		releasedButtons[button] = true;
	}

	buttonStates[button] = action != GLFW_RELEASE;
}

float Mouse::getX()
{
	return coordinates.x;
}

float Mouse::getY()
{
	return coordinates.y;
}

const glm::vec2& Mouse::getCoordinates()
{
	return coordinates;
}

bool Mouse::isButtonPressed(int button)
{
	bool x = pressedButtons[button];
	pressedButtons[button] = false;
	return x;
}

bool Mouse::isButtonReleased(int button)
{
	bool x = releasedButtons[button];
	releasedButtons[button] = false;
	return x;
}

bool Mouse::getButtonState(int button)
{
	return buttonStates[button];
}