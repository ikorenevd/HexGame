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

	float defaultUpkeep;
	float upkeep;

	int defaultStorageLimit;
	int storageLimit;

	std::unordered_map<enum ResourseType, float> storage;
	std::shared_ptr<Texture> texture;

	Building(const std::shared_ptr<Tile>& tile);

	virtual void update();

	void setTile(const std::shared_ptr<Tile>& value);
	void setFrozen(bool setFrozen);
	void setStorage(ResourseType type, int value);
	void addStorage();

	std::shared_ptr<Texture> getTexture();
	bool getFrozen();
	bool getFunctioning();
	int getUsedStorage();
	int getResourseAmount(enum ResourseType);
	float getUpkeep();
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
		frozen = false;
		functioning = true;
		defaultUpkeep, upkeep = 50 / 3600.;
		defaultStorageLimit, storageLimit = 500;

		texture = TextureManager::get("factory");

		storage[ResourseType::RawWood] = 0;
		storage[ResourseType::ProcessedWood] = 0;
		storage[ResourseType::Plank] = 0;
	}

	void update() override
	{
		if (!frozen)
		{
			if (this->getUsedStorage() < storageLimit)
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