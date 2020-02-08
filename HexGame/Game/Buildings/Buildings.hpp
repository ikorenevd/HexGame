#include <Engine\Engine.hpp>
#include <Engine\Core\Manager.hpp>
#include <Game/Buildings/ResourceTypes.hpp>
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
	std::shared_ptr<Texture> texture;
	std::vector<std::shared_ptr<Building>> selectedTransportingTargets;

	Building(const std::shared_ptr<Tile>& tile);

	virtual void update();

	void setTile(const std::shared_ptr<Tile>& value);
	void setFrozen(bool setFrozen);
	void setStorage(ResourseType type, float value);
	void setTransportationTarget(std::shared_ptr<Building>& building);
	void deleteTransportationTarget(std::shared_ptr<Building>& building);

	std::shared_ptr<Texture> getTexture();
	bool isFrozen();
	bool isFunctioning();
	bool isStorageFull();
	int getUsedStorage();
	int getResourseAmount(ResourseType);
	float getUpkeep();
	std::vector<std::shared_ptr<Building>> getTransportationTargets();
	std::shared_ptr<Tile>& getTile();
private:
	std::shared_ptr<Tile> tile;
};

class ExtensionBuilding : public Building
{
public:
	ExtensionBuilding(const std::shared_ptr<Tile>& tile);
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

		texture = TextureManager::get("Sawmill");

		storage[ResourseType::RawWood] = 0;
		storage[ResourseType::ProcessedWood] = 0;
		storage[ResourseType::Plank] = 0;
	}

	void update() override
	{
		if (!frozen)
		{
			if ( !isStorageFull() )
			{
				functioning = true;

				if (storage[ResourseType::RawWood] >= 90 / 3600.)
				{
					storage[ResourseType::ProcessedWood] += 45 / 3600.;
					storage[ResourseType::RawWood] -= 90 / 3600.;
				}

				if (storage[ResourseType::ProcessedWood] >= 15 / 3600.)
				{
					storage[ResourseType::Plank] += 45 / 3600.;
					storage[ResourseType::ProcessedWood] -= 15 / 3600.;
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

		texture = TextureManager::get("Felled");

		storage[ResourseType::RawWood] = 0;
	}

	void update() override
	{
		if (!frozen)
		{
			if (!isStorageFull())
			{
				functioning = true;
				storage[ResourseType::RawWood] += 45 / 3600.;
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