#pragma once

#include <Engine/Engine.hpp>

#include <Game/Map/TerrainType.hpp>

class Tile : public GameObject
{
public:
	Tile(const glm::ivec3& coordinates, TerrainType type);

	const glm::ivec3& getCoordinates() const;

	TerrainType getTerrainType() const;

	bool isCrossable() const;

	void update(const glm::vec2& mouseCoord) override;
private:
	glm::ivec3 coordinates;
	TerrainType type;
};
