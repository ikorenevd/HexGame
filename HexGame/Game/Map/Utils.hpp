#pragma once

#include <vector>

#include <Engine/Engine.hpp>

class HexUtils
{
public:
	static const std::vector<glm::ivec3> neighborsCoordinates;

	float outerRadius = 25.f;
	float innerRadius = outerRadius * 0.866025;
};

const std::vector<glm::ivec3> HexUtils::neighborsCoordinates = {
		glm::ivec3(0, 1, -1),
		glm::ivec3(-1, 1, 0),
		glm::ivec3(-1, 0, 1),
		glm::ivec3(0, -1, 1),
		glm::ivec3(1, -1, 0),
		glm::ivec3(1, 0, -1)
};
