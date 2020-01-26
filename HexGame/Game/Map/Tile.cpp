#include <Game/Map/Tile.hpp>

#include <Game/Map/HexUtils.hpp>

Tile::Tile(const glm::ivec3& coordinates, TerrainType type) :
	coordinates(coordinates),
	type(type)
{
	//setScale(glm::vec2(80.f)); // размер
	setPosition(glm::vec2((float)(coordinates.x + (float)coordinates.y / 2) * 80.f, (float)coordinates.y * 0.86f * 80.f));
}

const glm::ivec3& Tile::getCoordinates() const
{
	return coordinates;
}

TerrainType Tile::getTerrainType() const
{
	return type;
}

bool Tile::isCrossable() const
{
	return isTerrainCrossable(type);
}

void Tile::update(const glm::vec2& mouseCoord)
{
		if ((mouseCoord.x - getPosition().x) * (mouseCoord.x - getPosition().x)+ (mouseCoord.y - getPosition().y) * (mouseCoord.y - getPosition().y) <= (40.f  * 0.86f) * (40.f * 0.86f))
		{
			if (Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				type = TerrainType::Flatland;
			}
			if (Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
			{
				type = TerrainType::Mountain;
			}
			if (Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE))
			{
				type = TerrainType::Hill;
			}
		}
}
