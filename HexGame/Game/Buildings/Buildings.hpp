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
	std::unordered_map<ResourseType, int> productionSpeed;
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
	void setExtension(std::shared_ptr<Building>& building);
	void deleteTransportationTarget(std::shared_ptr<Building> building);

	std::shared_ptr<Texture> getTexture();
	bool isFrozen();
	bool isFunctioning();
	bool isStorageFull();
	int getUsedStorage();
	int getResourseAmount(ResourseType);
	int getProduction(ResourseType);
	float getUpkeep();
	int getExtensionAmount(BuildingType type);
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



class Sawmill : public MainBuilding
{
public:
	Sawmill(const std::shared_ptr<Tile>& tile) : MainBuilding(tile)
	{
		upkeep = 50 / 3600.;
		storageLimit = 500;

		buildingType = BuildingType::Sawmill;
		texture = TextureManager::get("Sawmill");

		storage[ResourseType::RawWood] = 0;

		storage[ResourseType::ProcessedWood] = 0;
		productionSpeed[ResourseType::ProcessedWood] = 45;

		storage[ResourseType::Plank] = 0;
		productionSpeed[ResourseType::Plank] = 45;
	}

	void update() override
	{
		if (!frozen)
		{
			if ( !isStorageFull() )
			{
				functioning = true;

				if (storage[ResourseType::RawWood] >= productionSpeed[ResourseType::ProcessedWood] * 2 / 3600.)
				{
					storage[ResourseType::ProcessedWood] += productionSpeed[ResourseType::ProcessedWood] / 3600.;
					storage[ResourseType::RawWood] -= productionSpeed[ResourseType::ProcessedWood] * 2 / 3600.;
				}

				if (storage[ResourseType::ProcessedWood] >= productionSpeed[ResourseType::Plank] / 3 / 3600.)
				{
					storage[ResourseType::Plank] += productionSpeed[ResourseType::Plank] / 3600.;
					storage[ResourseType::ProcessedWood] -= productionSpeed[ResourseType::Plank] / 3 / 3600.;
				}
				else
				{
					functioning = false;
				}
			}
			else
			{
				functioning = false;
			}
		}
	}
};

class Felled : public MainBuilding
{
public:
	Felled(const std::shared_ptr<Tile>& tile) : MainBuilding(tile)
	{
		upkeep = 40 / 3600.;
		storageLimit = 1000;

		buildingType = BuildingType::Felled;
		texture = TextureManager::get("Felled");

		storage[ResourseType::RawWood] = 0;
		productionSpeed[ResourseType::RawWood] = 45;

	}

	void update() override
	{
		if (!frozen)
		{
			if (!isStorageFull())
			{
				functioning = true;
				storage[ResourseType::RawWood] += productionSpeed[ResourseType::RawWood] / 3600.;
			}
			else
			{
				functioning = false;
			}
		}
	}
};

class Mine : public MainBuilding
{
public:
	Mine(const std::shared_ptr<Tile>& tile) : MainBuilding(tile)
	{
		upkeep = 75 / 3600.;
		storageLimit = 1500;

		buildingType = BuildingType::Mine;
		texture = TextureManager::get("Mine");

		storage[ResourseType::RawWood] = 0;
	}

	void update() override
	{
		if (!frozen)
		{
			if (!isStorageFull())
			{
				functioning = true;
				storage[ResourseType::Ore] += 50 / 3600.;
				storage[ResourseType::PreciousOre] += 15 / 3600.;
			}
			else
			{
				functioning = false;
			}
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