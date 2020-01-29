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
	std::vector<std::shared_ptr<Tile>> result;

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
			result.push_back(t);
		}
	}

	return result;
}

const std::vector<std::shared_ptr<Tile>> Map::getTilesInRange(const std::shared_ptr<Tile>& tile, int radius) const
{
	 std::vector<std::shared_ptr<Tile>> result;

	 auto coord = tile->getCoordinates();
	 for (int x = coord.x - radius; x <= coord.x + radius; x++)
		 for (int y = coord.y - radius; y <= coord.y + radius; y++)
			 for (int z = coord.z - radius; z <= coord.z + radius; z++)
				 if (x + y + z == 0)
				 {
					 std::shared_ptr<Tile> t = getTile(glm::ivec3(x, y, z));
					 if (t != nullptr)
						result.push_back(getTile(glm::ivec3(x, y, z)));
				 }

	 return result;
}

const std::vector<std::shared_ptr<Tile>> Map::getPath(const std::shared_ptr<Tile>& start, const std::shared_ptr<Tile>& end) const
{
	std::vector<std::shared_ptr<Tile>> result;

	glm::ivec3 startCoord = start->getCoordinates();
	glm::ivec3 endCoord = end->getCoordinates();

	///

	return result;
}

const int Map::getDistance(const std::shared_ptr<Tile>& start, const std::shared_ptr<Tile>& end) const
{
	glm::ivec3 startCoord = start->getCoordinates();
	glm::ivec3 endCoord = end->getCoordinates();

	return (abs(startCoord.x - endCoord.x) + abs(startCoord.y - endCoord.y) + abs(startCoord.z - endCoord.z)) / 2;
}