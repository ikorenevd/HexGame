#include <Engine\Engine.hpp>
#include <map>

class Tile;

enum class ResourseType
{	
	RawWood = 0,
	ProcessedWood,
	Plank,

	Ore,
	PreciousOre,
	Coal,
	Stone,

	Metal,
	PreciousMetal,

	Machine,
	Rail,
	Beam,
	Wearpon,
	Jewelry
};

class Building : public Transformable
{
public:
	static int cost;
	static int defaultUpkeep;
	std::map<enum ResourseType, int> storage;

	Building(const std::shared_ptr<Tile>& tile);

	void setTile(const std::shared_ptr<Tile>& value);

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
	std::vector<std::shared_ptr<ExtensionBuilding>> extensionBuildings;

	MainBuilding(const std::shared_ptr<Tile>& tile);
};