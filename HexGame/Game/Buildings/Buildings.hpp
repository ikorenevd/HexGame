#include <Engine\Engine.hpp>
#include <Game/Buildings/ResourceTypes.hpp>
#include <unordered_map>

class Tile;

class Building : public Transformable
{
public:
	static int buildingCost;
	static float defaultUpkeep;
	int defaultStorageLimit;
	int storageLimit;
	std::unordered_map<enum ResourseType, float> storage;

	Building(const std::shared_ptr<Tile>& tile);

	void setTile(const std::shared_ptr<Tile>& value);
	void changeStorage(ResourseType type, int value);
	void extensionStorage();

	int getUsedStorage();
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
		defaultUpkeep = 50/60.;
		defaultStorageLimit = 100;
		storageLimit = 100;

		storage[ResourseType::RawWood] = 0;
		storage[ResourseType::ProcessedWood] = 0;
		storage[ResourseType::Plank] = 0;
	}

	void update()
	{
		if (this->getUsedStorage() < storageLimit)
		{
			if (storage[ResourseType::RawWood] >= 90 / 60.)
			{
				storage[ResourseType::ProcessedWood] += 45 / 60.;
				storage[ResourseType::RawWood] -= 90 / 60.;
			}

			if (storage[ResourseType::ProcessedWood] >= 15 / 60.)
			{
				storage[ResourseType::Plank] += 45 / 60.;
				storage[ResourseType::ProcessedWood] -= 15 / 60.;
			}
		}
	}
};