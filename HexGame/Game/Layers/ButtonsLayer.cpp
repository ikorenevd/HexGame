#include <Game/Layers/ButtonsLayer.hpp>

Button::Button(const glm::vec2& pos, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, const std::string& name) :
	Transformable(pos, scale),
	texture(texture),
	name(name)
{
}

const std::shared_ptr<Texture>& Button::getTexture() const
{
	return texture;
}

bool Button::contains(const glm::vec2& point) const
{
	auto pos = getPosition();
	auto size = getScale();

	if ((pos.x + size.x) >= point.x &&
		(pos.x - size.x) <= point.x &&
		(pos.y + size.y) >= point.y &&
		(pos.y - size.y) <= point.y)
	{
		return true;
	};

	return false;
}

std::shared_ptr<Building> Button::buildBuilding(std::shared_ptr<Tile> tile)
{
	if (name == "Sawmill") return std::make_shared<Sawmill>(tile);
	if (name == "Felled") return std::make_shared<Felled>(tile);
	if (name == "Mine") return std::make_shared<Mine>(tile);
}

int Button::getBuildingCost()
{
	if (name == "Sawmill") return Sawmill::cost;
	if (name == "Felled") return Felled::cost;
	if (name == "Mine") return Mine::cost;
}