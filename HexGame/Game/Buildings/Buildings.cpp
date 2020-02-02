#include <Game/Buildings/Buildings.hpp>

#include <Game/Map/Tile.hpp>

Building::Building(const std::shared_ptr<Tile>& tile) :
	tile(tile)
{
	setPosition(tile->getPosition());
	setScale(glm::vec2(60.f));
}

void Building::setTile(const std::shared_ptr<Tile>& value)
{
	tile = value;

	setPosition(tile->getPosition());
}

const std::shared_ptr<Tile>& Building::getTile() const
{
	return tile;
}

void Building::changeStorage(ResourseType type, int value)
{
	storage[type] += value;
}

void Building::extensionStorage()
{
 	storageLimit += defaultStorageLimit * 1.5;
}

int  Building::getUsedStorage()
{
	int storageUsed = 0;

	for (auto i : storage)
	{
		storageUsed += resourceSize(i.first) * i.second;
	}

	return storageUsed;
}

ExtensionBuilding::ExtensionBuilding(const std::shared_ptr<Tile>& tile) :
	Building(tile)
{
}

MainBuilding::MainBuilding(const std::shared_ptr<Tile>& tile) :
	Building(tile)
{
}
