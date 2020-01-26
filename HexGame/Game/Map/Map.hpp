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

	void update(const glm::vec2& mouseCoord);	
private:
	glm::ivec2 size;

	std::vector<std::shared_ptr<Tile>> tiles;
};
