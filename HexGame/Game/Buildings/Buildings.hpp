#include <Engine\Engine.hpp>
#include <Game/Buildings/ResourceTypes.hpp>
#include <unordered_map>

class Tile;

class Building : public Transformable
{
public:
	int buildingCost;
	float defaultUpkeep;
	float upkeep;
	int defaultStorageLimit;
	int storageLimit;
	std::unordered_map<enum ResourseType, float> storage;

	Building(const std::shared_ptr<Tile>& tile);

	void setTile(const std::shared_ptr<Tile>& value);
	void changeStorage(ResourseType type, int value);
	void extensionStorage();
	virtual void update();

	int getUsedStorage();
	float getUpkeep();
	const int getResourseAmount(enum ResourseType);
	const std::shared_ptr<Tile>& getTile() const;
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
		buildingCost = 150;
		defaultUpkeep, upkeep = 50 / 3600.;
		defaultStorageLimit, storageLimit = 500;

		storage[ResourseType::RawWood] = 25;
		storage[ResourseType::ProcessedWood] = 0;
		storage[ResourseType::Plank] = 0;

		std::cout << "Sawmill is built ";
	}

	void update() override
	{
		if (this->getUsedStorage() < storageLimit)
		{
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
		}
	}
};