#pragma once

#include <Engine/Engine.hpp>

class Tile;

class Map
{
public:
	Map(const glm::ivec2& size);

	const glm::ivec2& getSize() const;

	const std::vector<std::shared_ptr<Tile>>& getNeighbors(const std::shared_ptr<Tile>& tile) const;

	const std::shared_ptr<Tile>& getTile(const glm::ivec3& coordinates) const;
private:
	glm::ivec2 size;

	std::vector<std::shared_ptr<Tile>> tiles;
};
