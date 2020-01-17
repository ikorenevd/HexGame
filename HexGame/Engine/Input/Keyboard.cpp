#include <Engine/Input/Keyboard.hpp>

bool Keyboard::keyStates[GLFW_KEY_LAST] = { 0 };
bool Keyboard::pressedKeys[GLFW_KEY_LAST] = { 0 };
bool Keyboard::releasedKeys[GLFW_KEY_LAST] = { 0 };

void Keyboard::callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key < 0)
		return;

	if (action != GLFW_RELEASE && keyStates[key] == false)
	{
		pressedKeys[key] = true;
		releasedKeys[key] = false;
	}

	if (action == GLFW_RELEASE && keyStates[key] == true)
	{
		pressedKeys[key] = false;
		releasedKeys[key] = true;
	}

	keyStates[key] = action != GLFW_RELEASE;
}

bool Keyboard::isKeyPressed(int key)
{
	bool x = pressedKeys[key];
	pressedKeys[key] = false;
	return x;
}

bool Keyboard::isKeyReleased(int key)
{
	bool x = releasedKeys[key];
	releasedKeys[key] = false;
	return x;
}

bool Keyboard::getKeyState(int key)
{
	return keyStates[key];
}
