#pragma once

#include <vector>

#include <Engine/Engine.hpp>

class HexUtils
{
public:
	static const std::vector<glm::ivec3> neighborsCoordinates;

	static float outerRadius;
	static float innerRadius;

	static const float vertices[2 * 4 + 2 * 4];
};
