#pragma once

#include <Engine/Engine.hpp>
#include <Game/Layers/ButtonsLayer.hpp>

class Map;

enum class UI
{
	Default = 0,
	Transportation,
	Extension
};


class MapLayer : public Layer
{
public:
	MapLayer(const std::shared_ptr<Map>& map);

	virtual void update() override;
	virtual void render() override;
private:
	std::shared_ptr<Map> map;
	std::vector<std::shared_ptr<Building>> buildings;
	std::unordered_map<ResourseType, int> storageMap;

	std::vector<std::shared_ptr<Button>> buttonsBuildings;
	std::vector<std::shared_ptr<Button>> buttonsExtensionBuildings;
	std::vector<std::shared_ptr<Button>> buttonsResources;

	std::shared_ptr<View> viewGame;
	std::shared_ptr<View> viewUI;
	UI interface;
	float speed = 2.f;;

	bool treasuryEmpty;
	float treasuryMoney;
	float totalUpkeep;
	double lastTime;

	std::shared_ptr<Button> pickedBuildingButton;
	std::shared_ptr<Button> pickedResourceButton;

	std::shared_ptr<Tile> selectedTile;
	std::shared_ptr<Tile> selectedExtensionTile;
	std::shared_ptr<Tile> selectedTransportationTile;

	std::shared_ptr<Building> selectedBuilding;
	std::shared_ptr<Building> selectedExtensionBuilding;
	std::shared_ptr<Building> selectedTransportationBuilding;

	std::shared_ptr<Tile> pointedTile;

	std::shared_ptr<VertexArray> vao;
};
