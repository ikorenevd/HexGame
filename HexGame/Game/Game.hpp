#pragma once

#include <iostream>

#include <Engine/Engine.hpp>

class TestLayer : public Layer
{
public:
	TestLayer() : Layer("TestLayer")
	{
	}

	virtual void render() override
	{
	}
};

class Game : public Application
{
public:
	Game() : Application(std::string("Game"), glm::ivec2(1280, 720))
	{
		this->getWindow()->setVSync(true);
	}

	virtual void pushingLayers() override
	{
		pushLayer(new TestLayer);
	}
};
