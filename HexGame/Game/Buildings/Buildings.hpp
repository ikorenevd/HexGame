#include <Engine\Engine.hpp>
#include <Game/Buildings/ResourceTypes.hpp>
#include <unordered_map>

class Tile;

class Building : public Transformable
{
public:
	bool active;
	float defaultUpkeep;
	float upkeep;
	int defaultStorageLimit;
	int storageLimit;
	std::unordered_map<enum ResourseType, float> storage;

	Building(const std::shared_ptr<Tile>& tile);

	void setTile(const std::shared_ptr<Tile>& value);
	void setActive(bool setActive);
	void setStorage(ResourseType type, int value);
	void addStorage();
	virtual void update();

	bool getActive();
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
	static int cost;

	Sawmill(const std::shared_ptr<Tile>& tile) : MainBuilding(tile)
	{
		defaultUpkeep, upkeep = 50 / 3600.;
		defaultStorageLimit, storageLimit = 500;

		storage[ResourseType::RawWood] = 0;
		storage[ResourseType::ProcessedWood] = 0;
		storage[ResourseType::Plank] = 0;
	}

	void update() override
	{
		if (active)
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
				else
				{
					active = false;
				}
			}
			else
			{
				active = false;
			}
		}
	}
};