#include <Game/Map/HexUtils.hpp>

const std::vector<glm::ivec3> HexUtils::neighborsCoordinates = {
		glm::ivec3(0, 1, -1),
		glm::ivec3(-1, 1, 0),
		glm::ivec3(-1, 0, 1),
		glm::ivec3(0, -1, 1),
		glm::ivec3(1, -1, 0),
		glm::ivec3(1, 0, -1)
};
