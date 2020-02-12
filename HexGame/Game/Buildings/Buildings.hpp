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
	int getStorage(ResourseType type);
	int getUsedStorage();
	int getResourseAmount(ResourseType);
	int getProduction(ResourseType);
	std::unordered_map<ResourseType, int> getAllProduction();
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
		storage[ResourseType::ProcessedWood] = 0;
		productionSpeed[ResourseType::ProcessedWood] = 30;	
	}

	void update() override
	{
		if (!frozen)
		{
			if ( !isStorageFull() )
			{
				if (storage[ResourseType::RawWood] >= productionSpeed[ResourseType::ProcessedWood] / 3 / 3600.)
				{
					functioning = true;
					storage[ResourseType::ProcessedWood] += productionSpeed[ResourseType::ProcessedWood] / 3600.;
					storage[ResourseType::RawWood] -= productionSpeed[ResourseType::ProcessedWood] / 3 / 3600.;
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
		storage[ResourseType::Plank] = 0;
		productionSpeed[ResourseType::Plank] = 90;
		storage[ResourseType::Furniture] = 0;
		productionSpeed[ResourseType::Furniture] = 15;
	}

	void update() override
	{
		if (!frozen)
		{
			if (!isStorageFull())
			{
				if (storage[ResourseType::ProcessedWood] >= productionSpeed[ResourseType::Plank] / 3 / 3600.)
				{
					functioning = true;
					storage[ResourseType::Plank] += productionSpeed[ResourseType::Plank] / 3600.;
					storage[ResourseType::ProcessedWood] -= productionSpeed[ResourseType::Plank] / 3 / 3600.;
				}
				else
					functioning = false;

				if (storage[ResourseType::ProcessedWood] >= productionSpeed[ResourseType::Furniture] * 2 / 3600.)
				{
					functioning = true;
					storage[ResourseType::Furniture] += productionSpeed[ResourseType::Furniture] / 3600.;
					storage[ResourseType::ProcessedWood] -= productionSpeed[ResourseType::Furniture] * 2 / 3600.;
				}
				else
					functioning = false;
			}
			else
				functioning = false;
		}
	}
};

class Foundry : public MainBuilding
{
public:
	Foundry(const std::shared_ptr<Tile>& tile) : MainBuilding(tile)
	{
		upkeep = 50 / 3600.;
		storageLimit = 1000;

		buildingType = BuildingType::Foundry;
		texture = TextureManager::get("Foundry");

		storage[ResourseType::Ore] = 0;
		storage[ResourseType::PreciousOre] = 0;
		storage[ResourseType::Coal] = 0;
		storage[ResourseType::Metal] = 0;
		productionSpeed[ResourseType::Metal] = 50;
		storage[ResourseType::PreciousMetal] = 0;
		productionSpeed[ResourseType::PreciousMetal] = 25;
	}

	void update() override
	{
		if (!frozen)
		{
			if (!isStorageFull())
			{
				functioning = true;

				if (storage[ResourseType::Coal] >= (productionSpeed[ResourseType::Metal] * 2 + productionSpeed[ResourseType::PreciousMetal]) / 3600.)
				{
					if (storage[ResourseType::Ore] >= productionSpeed[ResourseType::Metal] * 2 / 3600.)
					{
						functioning = true;
						storage[ResourseType::Metal] += productionSpeed[ResourseType::Metal] / 3600.;
						storage[ResourseType::Ore] -= productionSpeed[ResourseType::Metal] * 2 / 3600.;
						storage[ResourseType::Coal] -= productionSpeed[ResourseType::Metal] * 2 / 3600.;
					}
					else
						functioning = false;

					if (storage[ResourseType::PreciousOre] >= productionSpeed[ResourseType::PreciousMetal] / 3600.)
					{
						functioning = true;
						storage[ResourseType::PreciousMetal] += productionSpeed[ResourseType::PreciousMetal] / 3600.;
						storage[ResourseType::PreciousOre] -= productionSpeed[ResourseType::PreciousMetal] / 3600.;
						storage[ResourseType::Coal] -= productionSpeed[ResourseType::PreciousMetal] / 3600.;
					}
					else
							functioning = false;
				}
				else
					functioning = false;
			}
			else
				functioning = false;
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

		storage[ResourseType::Ore] = 0;
		productionSpeed[ResourseType::Ore] = 25;
		storage[ResourseType::PreciousOre] = 0;
		productionSpeed[ResourseType::PreciousOre] = 10;
		storage[ResourseType::Coal] = 0;
		productionSpeed[ResourseType::Coal] = 30;
	}

	void update() override
	{
		if (!frozen)
		{
			if (!isStorageFull())
			{
				functioning = true;
				storage[ResourseType::Ore] += productionSpeed[ResourseType::Ore] / 3600.;
				storage[ResourseType::PreciousOre] += productionSpeed[ResourseType::PreciousOre] / 3600.;
				storage[ResourseType::Coal] += productionSpeed[ResourseType::Coal] / 3600.;
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