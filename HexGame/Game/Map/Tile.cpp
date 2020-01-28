#include <Game/Map/Tile.hpp>

#include <math.h>

#include <Game/Map/HexUtils.hpp>

#define sqr(x) (x) * (x)

Tile::Tile(const glm::ivec3& coordinates, TerrainType type) :
	coordinates(coordinates),
	type(type)
{
	setScale(glm::vec2(80.f)); // размер
	setPosition(glm::vec2((float)(coordinates.x + (float)coordinates.y / 2) * 0.9f * 80.f, (float)coordinates.y * 0.9f * 0.86f * 80.f));
}

const glm::ivec3& Tile::getCoordinates() const
{
	return coordinates;
}

void Tile::setTerrainType(TerrainType value)
{
	type = value;
}

TerrainType Tile::getTerrainType() const
{
	return type;
}

bool Tile::isCrossable() const
{
	return isTerrainCrossable(type);
}

bool Tile::contains(const glm::vec2& point) const
{
	float radius = getScale().x / 2;
	return (sqr(point.x - getPosition().x) + sqr(point.y - getPosition().y) <= sqr(radius * 0.86f));
}
