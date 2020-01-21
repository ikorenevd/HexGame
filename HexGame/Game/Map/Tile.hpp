#pragma once

#include <Engine/Engine.hpp>

#include <Game/Map/TerrainType.hpp>

class Tile
{
public:
	Tile(const glm::ivec3& coordinates, TerrainType type);

	const glm::ivec3& getCoordinates() const;

	TerrainType getTerrainType() const;

	bool isCrossable() const;
private:
	glm::ivec3 coordinates;
	TerrainType type;
};
