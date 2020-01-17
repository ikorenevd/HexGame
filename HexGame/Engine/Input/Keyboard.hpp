#pragma once

#include <Engine/Core/OpenGL.hpp>

class Keyboard
{
public:
	static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static bool isKeyPressed(int key);
	static bool isKeyReleased(int key);
	static bool getKeyState(int key);
private:
	static bool keyStates[];
	static bool pressedKeys[];
	static bool releasedKeys[];
};
