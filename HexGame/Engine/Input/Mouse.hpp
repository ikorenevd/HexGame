#pragma once

#include <Engine/Core/OpenGL.hpp>

class Mouse
{
public:
	static void posCallback(GLFWwindow* window, double _x, double _y);
	static void btnCallback(GLFWwindow* window, int button, int action, int mods);

	static float getX();
	static float getY();

	static const glm::vec2& getCoordinates();

	static bool isButtonPressed(int button);
	static bool isButtonReleased(int button);
	static bool getButtonState(int button);

private:
	static glm::vec2 coordinates;

	static bool buttonStates[];
	static bool pressedButtons[];
	static bool releasedButtons[];
};
