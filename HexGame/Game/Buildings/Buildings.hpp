#include <Engine\Engine.hpp>

class Tile;

class Building : public Transformable
{
public:
	Building(const std::shared_ptr<Tile>& tile);

	const std::shared_ptr<Tile>& getTile() const;
public:
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
