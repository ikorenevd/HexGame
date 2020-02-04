#pragma once

#include <Engine/Engine.hpp>
#include <Game/Layers/ButtonsLayer.hpp>

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
	std::vector<std::shared_ptr<Button>> buttons;
	std::unordered_map<ResourseType, int> storageMap;

	std::shared_ptr<View> view;
	std::shared_ptr<View> buttonView;
	float speed = 2.f;

	bool waitingBuilding;
	float treasuryMoney;
	float totalUpkeep;
	double lastTime;
	std::shared_ptr<Button> pressedButton;
	std::shared_ptr<Tile> selectedTile;

	std::shared_ptr<VertexArray> vao;
};
