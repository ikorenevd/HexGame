#include <Game/Buildings/Buildings.hpp>
#include <Game/Buildings/BuildingTypes.hpp>
#include <Game/Map/Tile.hpp>

Building::Building(const std::shared_ptr<Tile>& tile) :
	tile(tile)
{
	setPosition(tile->getPosition());
	setScale(glm::vec2(50));

	frozen = false;
	functioning = true;
}

void Building::update()
{

}

void Building::setTile(const std::shared_ptr<Tile>& value)
{
	tile = value;

	setPosition(tile->getPosition());
}

void Building::setExtension(BuildingType type, std::shared_ptr<Tile>& tile)
{
	if (type == BuildingType::Warehouse)
	{
		extensionBuildings.push_back(std::make_shared<Warehouse>(tile));
	}
}

std::vector<std::shared_ptr<Building>> Building::getExtensionBuildings()
{
	return extensionBuildings;
}

void Building::setFrozen(bool setActive)
{
	frozen = setActive;
}

void Building::setStorage(ResourseType type, float value)
{
	storage[type] += value;
}

std::shared_ptr<Tile>& Building::getTile()
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
		storageUsed += getResourceSize(i.first) * i.second;
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

void Building::setTransportationTarget(std::shared_ptr<Building>& building)
{
	int i = 0;
	bool exist = false;

	for (auto check : selectedTransportingTargets)
	{
		if (check == building)
		{
			exist = true;
			break;
		}

		i++;
	}

	if (exist)
		selectedTransportingTargets.erase(selectedTransportingTargets.begin() + i);
	else
		selectedTransportingTargets.push_back(building);
}

void Building::deleteTransportationTarget(std::shared_ptr<Building>& building)
{
	int i = 0;

	for (auto check : selectedTransportingTargets)
	{
		if (check == building)
		{
			selectedTransportingTargets.erase(selectedTransportingTargets.begin() + i);
			break;
		}

		i++;
	}
}

std::vector<std::shared_ptr<Building>> Building::getTransportationTargets()
{
	return selectedTransportingTargets;
}




ExtensionBuilding::ExtensionBuilding(const std::shared_ptr<Tile>& tile) : Building(tile)
{

}

MainBuilding::MainBuilding(const std::shared_ptr<Tile>& tile) : Building(tile)
{

}