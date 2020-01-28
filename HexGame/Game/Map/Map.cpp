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
	for (const std::shared_ptr<Tile>& tile : tiles)
		if (tile->getCoordinates() == coordinates)
			return tile;

	return nullptr;
}

const std::vector<std::shared_ptr<Tile>>& Map::getTiles() const
{
	return tiles;
}

const std::vector<std::shared_ptr<Tile>> Map::getNeighbors(const std::shared_ptr<Tile>& tile) const
{
	std::vector<std::shared_ptr<Tile>> tiles;

	std::vector<glm::ivec3> directions =
	{
		glm::ivec3(-1, 0, 1),
		glm::ivec3(-1, 1, 0),
		glm::ivec3(0, 1, -1),
		glm::ivec3(1, 0, -1),
		glm::ivec3(1, -1, 0),
		glm::ivec3(0, -1, 1),
	};

	auto tcoord = tile->getCoordinates();
	for (const glm::ivec3& offset : directions)
	{
		glm::ivec3 coord = tcoord + offset;
  		std::shared_ptr<Tile> t = getTile(coord);
		if (t != nullptr)
		{
			tiles.push_back(t);
		}
	}

	return tiles;
}
