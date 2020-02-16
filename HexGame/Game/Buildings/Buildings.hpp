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
		defaultProduction[ResourseType::RawWood] = 30;
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
		defaultProduction[ResourseType::RawWood] = -15;
		storage[ResourseType::ProcessedWood] = 0;
		defaultProduction[ResourseType::ProcessedWood] = 30;	
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

					storage[ResourseType::RawWood] += currentProduction[ResourseType::RawWood] / 3600.;
					storage[ResourseType::ProcessedWood] += currentProduction[ResourseType::ProcessedWood] / 3600.;
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
		defaultProduction[ResourseType::ProcessedWood] = -60;

		storage[ResourseType::Plank] = 0;
		defaultProduction[ResourseType::Plank] = 40;

		storage[ResourseType::Furniture] = 0;
		defaultProduction[ResourseType::Furniture] = 10;
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
		defaultProduction[ResourseType::Ore] = -100;

		storage[ResourseType::PreciousOre] = 0;
		defaultProduction[ResourseType::PreciousOre] = -100;

		storage[ResourseType::Coal] = 0;
		defaultProduction[ResourseType::Coal] = -150;

		storage[ResourseType::Metal] = 0;
		defaultProduction[ResourseType::Metal] = 50;

		storage[ResourseType::PreciousMetal] = 0;
		defaultProduction[ResourseType::PreciousMetal] = 50;
	}

	void update() override
	{
		currentProduction[ResourseType::Ore] = 0;
		currentProduction[ResourseType::PreciousOre] = 0;
		currentProduction[ResourseType::Coal] = 0;
		currentProduction[ResourseType::Metal] = 0;
		currentProduction[ResourseType::PreciousMetal] = 0;

		if (!frozen)
		{
			if (!isStorageFull())
			{
				if (storage[ResourseType::Coal] >= -defaultProduction[ResourseType::Coal] / 3600.)
				{
					if (storage[ResourseType::Ore] >= -defaultProduction[ResourseType::Ore] / 3600.)
					{
						functioning = true;
						currentProduction[ResourseType::Metal] = defaultProduction[ResourseType::Metal];
						currentProduction[ResourseType::Coal] = defaultProduction[ResourseType::Coal];
						currentProduction[ResourseType::Ore] = defaultProduction[ResourseType::Ore];

						storage[ResourseType::Metal] += currentProduction[ResourseType::Metal] / 3600.;
						storage[ResourseType::Coal] += currentProduction[ResourseType::Coal] / 2 / 3600.;
						storage[ResourseType::Ore] += currentProduction[ResourseType::Ore] / 3600.;
					}
					else
						functioning = false;

					if (storage[ResourseType::PreciousOre] >= -defaultProduction[ResourseType::PreciousOre] / 3600.)
					{
						functioning = true;
						currentProduction[ResourseType::PreciousMetal] = defaultProduction[ResourseType::PreciousMetal];
						currentProduction[ResourseType::Coal] = defaultProduction[ResourseType::Coal];
						currentProduction[ResourseType::PreciousOre] = defaultProduction[ResourseType::PreciousOre];

						storage[ResourseType::PreciousMetal] += currentProduction[ResourseType::PreciousMetal] / 3600.;
						storage[ResourseType::Coal] += currentProduction[ResourseType::Coal] / 2 / 3600.;
						storage[ResourseType::PreciousOre] += currentProduction[ResourseType::PreciousOre] / 3600.;
					}
				}
				else
					functioning = false;
			}
			else
				functioning = false;
		}
	}
};

class MachineShop : public MainBuilding
{
public:
	MachineShop(const std::shared_ptr<Tile>& tile) : MainBuilding(tile)
	{
		upkeep = 100 / 3600.;
		storageLimit = 1000;

		buildingType = BuildingType::MachineShop;
		texture = TextureManager::get("MachineShop");

		storage[ResourseType::Metal] = 0;
		defaultProduction[ResourseType::Metal] = -50;
		storage[ResourseType::Machine] = 0;
		defaultProduction[ResourseType::Machine] = 10;
	}

	void update() override
	{
		currentProduction[ResourseType::Metal] = 0;
		currentProduction[ResourseType::Machine] = 0;

		if (!frozen)
		{
			if (!isStorageFull())
			{
				if (storage[ResourseType::Metal] >= -defaultProduction[ResourseType::Machine] / 3600.)
				{
					functioning = true;
					currentProduction[ResourseType::Metal] = defaultProduction[ResourseType::Metal];
					currentProduction[ResourseType::Machine] = defaultProduction[ResourseType::Machine];

					storage[ResourseType::Metal] += currentProduction[ResourseType::Metal] / 3600.;
					storage[ResourseType::Machine] += currentProduction[ResourseType::Machine] / 3600.;
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
		storageLimit = 1000;

		buildingType = BuildingType::Mine;
		texture = TextureManager::get("Mine");

		storage[ResourseType::Coal] = 0;
		defaultProduction[ResourseType::Coal] = 60;

		storage[ResourseType::Ore] = 0;
		defaultProduction[ResourseType::Ore] = 40;

		storage[ResourseType::PreciousOre] = 0;
		defaultProduction[ResourseType::PreciousOre] = 20;

		storage[ResourseType::Stone] = 0;
		defaultProduction[ResourseType::Stone] = 80;
	}

	void update() override
	{
		currentProduction[ResourseType::Coal] = 0;
		currentProduction[ResourseType::Ore] = 0;
		currentProduction[ResourseType::PreciousOre] = 0;
		currentProduction[ResourseType::Stone] = 0;

		if (!frozen)
		{
			if (!isStorageFull())
			{
				functioning = true;

				currentProduction[ResourseType::Coal] = defaultProduction[ResourseType::Coal];
				currentProduction[ResourseType::Ore] = defaultProduction[ResourseType::Ore];
				currentProduction[ResourseType::PreciousOre] = defaultProduction[ResourseType::PreciousOre];
				currentProduction[ResourseType::Stone] = defaultProduction[ResourseType::Stone];

				storage[ResourseType::Coal] += currentProduction[ResourseType::Coal] / 3600.;
				storage[ResourseType::Ore] += currentProduction[ResourseType::Ore] / 3600.;
				storage[ResourseType::PreciousOre] += currentProduction[ResourseType::PreciousOre] / 3600.;
				storage[ResourseType::Stone] += currentProduction[ResourseType::Stone] / 3600.;
			}
			else
				functioning = false;
		}
	}
};

class Farm : public MainBuilding
{
public:
	Farm(const std::shared_ptr<Tile>& tile) : MainBuilding(tile)
	{
		upkeep = 50 / 3600.;
		storageLimit = 1000;

		buildingType = BuildingType::Farm;
		texture = TextureManager::get("Farm");

		storage[ResourseType::Cereal] = 0;
		defaultProduction[ResourseType::Cereal] = 75;
	}

	void update() override
	{
		currentProduction[ResourseType::Cereal] = 0;

		if (!frozen)
		{
			if (!isStorageFull())
			{
				functioning = true;

				currentProduction[ResourseType::Cereal] = defaultProduction[ResourseType::Cereal];

				storage[ResourseType::Cereal] += currentProduction[ResourseType::Cereal] / 3600.;
			}
			else
				functioning = false;
		}
	}
};

class TradingWarehouse : public MainBuilding
{
public:
	TradingWarehouse(const std::shared_ptr<Tile>& tile) : MainBuilding(tile)
	{
		functioning = true;
		upkeep = 100 / 3600.;
		storageLimit = 1000;

		for (int i = 0; i < 20; i++)
			storage[(ResourseType)i] = 0;

		for (int i = 0; i < 20; i++)
			defaultProduction[(ResourseType)i] = -50;

		buildingType = BuildingType::TradingWarehouse;
		texture = TextureManager::get("TradingWarehouse");
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