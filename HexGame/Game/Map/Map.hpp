#pragma once

#include <Engine/Engine.hpp>

class Tile;

class Map
{
public:
	Map(const glm::ivec2& size);

	const glm::ivec2& getSize() const;

	const std::shared_ptr<Tile>& getTile(const glm::ivec3& coordinates) const;

	const std::vector<std::shared_ptr<Tile>>& getTiles() const;

	const std::vector<std::shared_ptr<Tile>> getNeighbors(const std::shared_ptr<Tile>& tile) const;

	const std::vector<std::shared_ptr<Tile>> getTilesInRange(const std::shared_ptr<Tile>& tile, int radius) const;

	const std::vector<std::shared_ptr<Tile>> getPath(const std::shared_ptr<Tile>& start, const std::shared_ptr<Tile>& end) const;

	const int getDistance(const std::shared_ptr<Tile>& start, const std::shared_ptr<Tile>& end) const;
private:
	glm::ivec2 size;

	std::vector<std::shared_ptr<Tile>> tiles;
};