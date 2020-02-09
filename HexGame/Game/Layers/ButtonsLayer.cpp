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

	if ((pos.x + size.x / 2) >= point.x &&
		(pos.x - size.x / 2) <= point.x &&
		(pos.y + size.y / 2) >= point.y &&
		(pos.y - size.y / 2) <= point.y)
	{
		return true;
	};

	return false;
}

BuildingType Button::getBuildingType()
{
	if (name == "Sawmill") return BuildingType::Sawmill;
	if (name == "Felled") return BuildingType::Felled;
	if (name == "Mine") return BuildingType::Mine;

	if (name == "Warehouse") return BuildingType::Warehouse;
}

ResourseType Button::getResourceType()
{
	if (name == "RawWood") return ResourseType::RawWood;
}

std::string Button::getName()
{
	return name;
}