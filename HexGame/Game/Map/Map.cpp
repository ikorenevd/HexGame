#include <Game/Map/Map.hpp>

#include <Game/Map/Tile.hpp>
#include <Game/Map/TerrainType.hpp>
#include <Game/Map/HexUtils.hpp>

Map::Map(const glm::ivec2& s) :
	size(s)
{
	tiles.resize(size.x * size.y);

	int a = 0;
	for (int x = 0; x < size.x; x++)
		for (int y = 0; y < size.y; y++)
		{
			tiles[a] = std::make_shared<Tile>(glm::ivec3(x, y, -x - y), (TerrainType)(rand() % 3));
			a++;
		}
}

const glm::ivec2& Map::getSize() const
{
	return size;
}

const std::shared_ptr<Tile>& Map::getTile(const glm::ivec3& coordinates) const
{
	if (coordinates.x < 0 || coordinates.x > size.x || coordinates.y < 0 || coordinates.y > size.y)
		return nullptr;

	if (coordinates.x + coordinates.y + coordinates.z != 0)
		return nullptr;

	for (const std::shared_ptr<Tile>& tile : tiles)
	{
		if (tile->getCoordinates() == coordinates)
			return tile;
	}

	return tiles[coordinates.x * size.x + coordinates.y];
}

const std::vector<std::shared_ptr<Tile>>& Map::getTiles() const
{
	return tiles;
}

void Map::update(const glm::vec2& mouseCoord)
{
	for (auto tile : tiles)
	{
		tile->update(mouseCoord);
	}
}
