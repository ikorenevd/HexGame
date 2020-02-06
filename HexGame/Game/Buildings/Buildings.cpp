#include <Game/Buildings/Buildings.hpp>

#include <Game/Map/Tile.hpp>

Building::Building(const std::shared_ptr<Tile>& tile) :
	tile(tile)
{
	setPosition(tile->getPosition());
	setScale(glm::vec2(50));
}

void Building::update()
{

}

void Building::setTile(const std::shared_ptr<Tile>& value)
{
	tile = value;

	setPosition(tile->getPosition());
}

void Building::setFrozen(bool setActive)
{
	frozen = setActive;
}

void Building::setStorage(ResourseType type, float value)
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

std::shared_ptr<Texture> Building::getTexture()
{
	return texture;
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

int Building::getResourseAmount(ResourseType type)
{
	return storage[type];
}

bool Building::isFrozen()
{
	return frozen;
}

bool Building::isFunctioning()
{
	return functioning;
}

float Building::getUpkeep()
{
	return upkeep;
}

bool Building::isStorageFull()
{
	return getUsedStorage() >= storageLimit;
}

int Sawmill::cost = 150;
int Felled::cost = 200;
int Mine::cost = 250;

ExtensionBuilding::ExtensionBuilding(const std::shared_ptr<Tile>& tile) :
	Building(tile)
{
}

MainBuilding::MainBuilding(const std::shared_ptr<Tile>& tile) :
	Building(tile)
{
}