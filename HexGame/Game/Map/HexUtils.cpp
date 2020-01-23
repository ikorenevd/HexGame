#include <Game/Map/HexUtils.hpp>

float HexUtils::outerRadius = 25.f;
float HexUtils::innerRadius = HexUtils::outerRadius * 0.866f;

const std::vector<glm::ivec3> HexUtils::neighborsCoordinates = {
		glm::ivec3(0, 1, -1),
		glm::ivec3(-1, 1, 0),
		glm::ivec3(-1, 0, 1),
		glm::ivec3(0, -1, 1),
		glm::ivec3(1, -1, 0),
		glm::ivec3(1, 0, -1)
};

const float HexUtils::vertices[2 * 4 + 2 * 4] = {
	-HexUtils::outerRadius, -HexUtils::innerRadius, 0.f, 0.f,
	-HexUtils::outerRadius,  HexUtils::innerRadius, 0.f, 1.f,
	 HexUtils::outerRadius,  HexUtils::innerRadius, 1.f, 1.f,
	 HexUtils::outerRadius, -HexUtils::innerRadius, 1.f, 0.f,
};

