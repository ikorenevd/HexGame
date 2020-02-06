
#pragma once

#include <iostream>

#include <Engine/Engine.hpp>

#include <Game/Map/Map.hpp>
#include <Game/Map/Tile.hpp>

#include <Game/Layers/MapLayer.hpp>
#include <Game/Layers/ButtonsLayer.hpp>

class Game : public Application
{
public:
	Game() : Application(std::string("Hex City"), glm::ivec2(1280, 720))
	{
		this->getWindow()->setVSync(false);
	}

	virtual void pushingLayers() override
	{
		map = std::make_shared<Map>(glm::ivec2(20, 20));

		pushLayer(new MapLayer(map));
	}
private:
	std::shared_ptr<Map> map;
};
