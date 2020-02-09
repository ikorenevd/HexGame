#pragma once

#include <map>
#include <Engine/Engine.hpp>
#include <Engine/Core/Manager.hpp>
#include <Game/Buildings/Buildings.hpp>
#include <Game/Buildings/BuildingTypes.hpp>

class Button : public Transformable
{
public:
	Button(const glm::vec2& pos, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, const std::string& name);

	bool contains(const glm::vec2& point) const;

	const std::shared_ptr<Texture>& getTexture() const;
	BuildingType getBuildingType();
	ResourseType getResourceType();
	std::string getName();
private:
	std::shared_ptr<Texture> texture;

	std::string name;
};
