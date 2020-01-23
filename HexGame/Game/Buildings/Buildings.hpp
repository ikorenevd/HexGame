#include <Engine\Engine.hpp>
#include <Game\Map\Tile.hpp>
#include <map>

class Building
{
public:
	std::map<std::string, int> storage;
	Building(const std::shared_ptr<Tile>& tile);

	const std::shared_ptr<Tile> &getTile() const;
};



class MainBuilding : public Building
{
public:
	std::vector<std::shared_ptr<ExtensionBuilding>&> extensionBuildings;		// Ampersands will drive me to the grave
	int workers;

	MainBuilding(const std::shared_ptr<Tile>& tile) : Building(tile) {		};

	int getWorkers() const;
};

class ExtensionBuilding : public Building
{
public:
	int workersBonus;

	ExtensionBuilding(const std::shared_ptr<Tile>& tile) : Building(tile) {		};

	int getWorkersBonus() const;
};



class Factory : public MainBuilding
{
public:
	int workers;

	Factory(const std::shared_ptr<Tile>& tile) : MainBuilding(tile) {		};

	int getWorkers() const;
};

class House : public MainBuilding
{	
public:
	int livers;

	House(const std::shared_ptr<Tile>& tile) : MainBuilding(tile) {		};

	int getLivers() const;
};