#include <Engine\Engine.hpp>
#include <Engine\Core\Manager.hpp>
#include <Game/Buildings/ResourceTypes.hpp>
#include <Game/Buildings/BuildingTypes.hpp>
#include <unordered_map>

class Tile;

class Building : public Transformable
{
public:
	bool frozen;
	bool functioning;

	float upkeep;
	int storageLimit;

	std::unordered_map<ResourseType, float> storage;
	std::unordered_map<ResourseType, int> defaultProduction;
	std::unordered_map<ResourseType, int> currentProduction;
	std::shared_ptr<Texture> texture;
	std::unordered_map<std::shared_ptr<Building>, ResourseType> selectedTransportingTargets;
	std::vector<std::shared_ptr<Building>> extensionBuildings;
	std::shared_ptr<Building> parent;
	BuildingType buildingType;

	Building(const std::shared_ptr<Tile>& tile);

	virtual void update();

	void setTile(const std::shared_ptr<Tile>& value);
	void setFrozen(bool setFrozen);
	void setStorage(ResourseType type, float value);
	void setTransportationTarget(std::shared_ptr<Building>& building, ResourseType type);
	void deleteTransportationTarget(std::shared_ptr<Building> building);
	void setExtension(std::shared_ptr<Building>& building);

	std::shared_ptr<Texture> getTexture();
	bool isFrozen();
	bool isFunctioning();
	bool isStorageFull();
	float getUpkeep();
	int getStorage(ResourseType type);
	int getUsedStorage();
	int getProduction(ResourseType);
	int getDefaultProduction(ResourseType);
	std::unordered_map<ResourseType, int> getProductions();
	std::unordered_map<ResourseType, int> getDefaultProductions();
	BuildingType getBuildingType();
	std::unordered_map<std::shared_ptr<Building>, ResourseType> getTransportationTargets();
	std::vector<std::shared_ptr<Building>> getExtensionBuildings();
	std::shared_ptr<Tile>& getTile();
	std::shared_ptr<Building> getParent();
private:
	std::shared_ptr<Tile> tile;
};

class ExtensionBuilding : public Building
{
public:
	ExtensionBuilding(const std::shared_ptr<Tile>& tile, std::shared_ptr<Building>& main);
};

class MainBuilding : public Building
{
public:
	MainBuilding(const std::shared_ptr<Tile>& tile);
};


// Здания
class Felled : public MainBuilding
{
public:
	Felled(const std::shared_ptr<Tile>& tile) : MainBuilding(tile)
	{
		upkeep = 25 / 3600.;
		storageLimit = 1000;

		buildingType = BuildingType::Felled;
		texture = TextureManager::get("Felled");

		storage[ResourseType::RawWood] = 0;
		defaultProduction[ResourseType::RawWood] = 20;
	}

	void update() override
	{
		currentProduction[ResourseType::RawWood] = 0;

		if (!frozen)
		{
			if (!isStorageFull())
			{
				functioning = true;
				currentProduction[ResourseType::RawWood] = defaultProduction[ResourseType::RawWood];
				storage[ResourseType::RawWood] += currentProduction[ResourseType::RawWood] / 3600.;
			}
			else
				functioning = false;
		}
	}
};

class Sawmill : public MainBuilding
{
public:
	Sawmill(const std::shared_ptr<Tile>& tile) : MainBuilding(tile)
	{
		upkeep = 50 / 3600.;
		storageLimit = 1000;

		buildingType = BuildingType::Sawmill;
		texture = TextureManager::get("Sawmill");

		storage[ResourseType::RawWood] = 0;
		defaultProduction[ResourseType::RawWood] = -10;
		storage[ResourseType::ProcessedWood] = 0;
		defaultProduction[ResourseType::ProcessedWood] = 20;	
	}

	void update() override
	{
		currentProduction[ResourseType::ProcessedWood] = 0;
		currentProduction[ResourseType::RawWood] = 0;

		if (!frozen)
		{
			if ( !isStorageFull() )
			{
				if (storage[ResourseType::RawWood] >= -defaultProduction[ResourseType::RawWood] / 3600.)
				{
					functioning = true;
					currentProduction[ResourseType::RawWood] = defaultProduction[ResourseType::RawWood];
					currentProduction[ResourseType::ProcessedWood] = defaultProduction[ResourseType::ProcessedWood];

					storage[ResourseType::ProcessedWood] += currentProduction[ResourseType::ProcessedWood] / 3600.;
					storage[ResourseType::RawWood] += currentProduction[ResourseType::ProcessedWood] / 3600.;
				}
				else
					functioning = false;
			}
			else
				functioning = false;
		}
	}
};

class FurnitureManufacture : public MainBuilding
{
public:
	FurnitureManufacture(const std::shared_ptr<Tile>& tile) : MainBuilding(tile)
	{
		upkeep = 50 / 3600.;
		storageLimit = 1000;

		buildingType = BuildingType::FurnitureManufacture;
		texture = TextureManager::get("FurnitureManufacture");

		storage[ResourseType::ProcessedWood] = 0;
		defaultProduction[ResourseType::ProcessedWood] = -50;

		storage[ResourseType::Plank] = 0;
		defaultProduction[ResourseType::Plank] = 40;

		storage[ResourseType::Furniture] = 0;
		defaultProduction[ResourseType::Furniture] = 5;
	}

	void update() override
	{
		currentProduction[ResourseType::ProcessedWood] = 0;
		currentProduction[ResourseType::Plank] = 0;
		currentProduction[ResourseType::Furniture] = 0;

		if (!frozen)
		{
			if (!isStorageFull())
			{
				if (storage[ResourseType::ProcessedWood] >= -defaultProduction[ResourseType::ProcessedWood] / 3600.)
				{
					functioning = true;
					currentProduction[ResourseType::ProcessedWood] = defaultProduction[ResourseType::ProcessedWood];
					currentProduction[ResourseType::Plank] = defaultProduction[ResourseType::Plank];
					currentProduction[ResourseType::Furniture] = defaultProduction[ResourseType::Furniture];

					storage[ResourseType::ProcessedWood] += currentProduction[ResourseType::ProcessedWood] / 3600.;
					storage[ResourseType::Plank] += currentProduction[ResourseType::Plank] / 3600.;
					storage[ResourseType::Furniture] += currentProduction[ResourseType::Furniture] / 3600.;
				}
				else
					functioning = false;
			}
			else
				functioning = false;
		}
	}
};

class Warehouse : public ExtensionBuilding
{
public:
	Warehouse(const std::shared_ptr<Tile>& tile, std::shared_ptr<Building>& main) : ExtensionBuilding(tile, main)
	{
		upkeep = 25 / 3600.;
		buildingType = BuildingType::Warehouse;
		texture = TextureManager::get("Warehouse");
	}
};