#pragma once

#include <Engine/Engine.hpp>

#include <Game/Buildings/Buildings.hpp>

class Map;

class MapLayer : public Layer
{
public:
	MapLayer(const std::shared_ptr<Map>& map);

	virtual void update() override;
	virtual void render() override;
private:
	std::shared_ptr<Map> map;
	std::vector<std::shared_ptr<Building>> buildings;

	std::shared_ptr<View> view;
	float speed = 2.f;

	float treasuryMoney;
	float totalUpkeep;
	std::shared_ptr<Tile> selectedTile;
	std::shared_ptr<Building> transportStart;
	std::shared_ptr<Building> transportEnd;
	bool transportWaiting;

	double lastTime;		// Debug

	std::shared_ptr<VertexArray> vao;
};
