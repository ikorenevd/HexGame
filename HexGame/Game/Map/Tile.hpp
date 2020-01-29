#pragma once

#include <Engine/Engine.hpp>

#include <Game/Map/TerrainType.hpp>

class Tile : public GameObject
{
public:
	Tile(const glm::ivec3& coordinates, TerrainType type);

	const glm::ivec3& getCoordinates() const;

	void setTerrainType(TerrainType value);
	TerrainType getTerrainType() const;

	bool isCrossable() const;

	bool contains(const glm::vec2& point) const override;

	const int getDistance(const std::shared_ptr<Tile>& target) const;
private:
	glm::ivec3 coordinates;
	TerrainType type;
};
