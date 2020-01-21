#include <Game/Map/Tile.hpp>

Tile::Tile(const glm::ivec3& coordinates, TerrainType type) :
	coordinates(coordinates),
	type(type)
{
}

const glm::ivec3& Tile::getCoordinates() const
{
	return coordinates;
}

TerrainType Tile::getTerrainType() const
{
	return type;
}

bool Tile::isCrossable() const
{
	return isTerrainCrossable(type);
}
