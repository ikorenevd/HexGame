#include <Game/Map/Tile.hpp>

#include <Game/Map/HexUtils.hpp>

Tile::Tile(const glm::ivec3& coordinates, TerrainType type) :
	coordinates(coordinates),
	type(type)
{
	setPosition(glm::vec2((float)(coordinates.x + (float)coordinates.y / 2) * 0.9f, (float)coordinates.y * 0.90f * 0.86f));
	setScale(glm::vec2(80.f)); // размер
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
