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

	extensionBuildings = {};
}

void Building::update()
{

}

void Building::setTile(const std::shared_ptr<Tile>& value)
{
	tile = value;

	setPosition(tile->getPosition());
}

void Building::setExtension(std::shared_ptr<Building>& building)
{
	auto index = std::find(extensionBuildings.begin(), extensionBuildings.end(), building);

	if (index != extensionBuildings.end())
		extensionBuildings.erase(index);
	else
		extensionBuildings.push_back(building);
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

BuildingType Building::getBuildingType()
{
	return buildingType;
}

int Building::getExtensionAmount(BuildingType type)
{
	int amount = 0;

	for (auto extensionBuiding : extensionBuildings)
	{
		if (extensionBuiding->getBuildingType() == type)
			amount++;
	}

	return amount;
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

int Building::getProduction(ResourseType type)
{
	return productionSpeed[type];
}

std::unordered_map<ResourseType, int> Building::getAllProduction()
{
	return productionSpeed;
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

int Building::getStorage(ResourseType type)
{
	return storage[type];
}

bool Building::isStorageFull()
{
	return getUsedStorage() >= storageLimit;
}

std::shared_ptr<Building> Building::getParent()
{
	return parent;
}

void Building::setTransportationTarget(std::shared_ptr<Building>& building, ResourseType type)
{
	auto index = selectedTransportingTargets.find(building);

	if (index == selectedTransportingTargets.end())
		selectedTransportingTargets.insert({ building, type });
}

void Building::deleteTransportationTarget(std::shared_ptr<Building> building)
{
	selectedTransportingTargets.erase(building);
}

std::unordered_map<std::shared_ptr<Building>, ResourseType> Building::getTransportationTargets()
{
	return selectedTransportingTargets;
}



ExtensionBuilding::ExtensionBuilding(const std::shared_ptr<Tile>& tile, std::shared_ptr<Building>& main) : Building(tile)
{
	parent = main;
}

MainBuilding::MainBuilding(const std::shared_ptr<Tile>& tile) : Building(tile)
{

}