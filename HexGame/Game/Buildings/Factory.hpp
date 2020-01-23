#include <Game\Buildings\Buildings.hpp>
#include <Engine\Engine.hpp>
#include <Game\Map\Tile.hpp>
#include <map>

class Sawmill : public ExtensionBuilding
{
public:
	Sawmill(const std::shared_ptr<Tile>& tile) : ExtensionBuilding(tile) {		};
};