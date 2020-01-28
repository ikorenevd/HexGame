#include <Game/Buildings/Buildings.hpp>

#include <Game/Map/Tile.hpp>

Building::Building(const std::shared_ptr<Tile>& tile) :
	tile(tile)
{
	setPosition(tile->getPosition());
	setScale(glm::vec2(60.f));
}

ExtensionBuilding::ExtensionBuilding(const std::shared_ptr<Tile>& tile) :
	Building(tile)
{
}

MainBuilding::MainBuilding(const std::shared_ptr<Tile>& tile) :
	Building(tile)
{
}
