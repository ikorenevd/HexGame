#include <Game/Buildings/Buildings.hpp>

#include <Game/Map/Tile.hpp>

Building::Building(const std::shared_ptr<Tile>& tile) :
	tile(tile)
{
	setPosition(tile->getPosition());
	setScale(glm::vec2(60.f));
}

void Building::update()
{

}

void Building::setTile(const std::shared_ptr<Tile>& value)
{
	tile = value;

	setPosition(tile->getPosition());
}

void Building::setActive(bool setActive)
{
	active = setActive;
}

void Building::setStorage(ResourseType type, int value)
{
	storage[type] += value;
}

void Building::addStorage()
{
 	if (storageLimit < defaultStorageLimit * 4)
		storageLimit += defaultStorageLimit * 1.5;
}

const std::shared_ptr<Tile>& Building::getTile() const
{
	return tile;
}

int Building::getUsedStorage()
{
	int storageUsed = 0;

	for (auto i : storage)
	{
		storageUsed += resourceSize(i.first) * i.second;
	}

	return storageUsed;
}

const int Building::getResourseAmount(enum ResourseType type)
{
	return storage[type];
}

bool Building::getActive()
{
	return active;
}

float Building::getUpkeep()
{
	return upkeep;
}

int Sawmill::cost = 150;

ExtensionBuilding::ExtensionBuilding(const std::shared_ptr<Tile>& tile) :
	Building(tile)
{
}

MainBuilding::MainBuilding(const std::shared_ptr<Tile>& tile) :
	Building(tile)
{
}