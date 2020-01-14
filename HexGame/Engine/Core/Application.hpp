#pragma once

#include <memory>
#include <string>
#include <vector>

#include <Engine/Core/OpenGL.hpp>

class Window;
class Layer;

class Application
{
public:
	Application(const std::string& name, const glm::ivec2& windowSize);

	virtual void update() final;
	virtual void render() final;

	virtual void pushingLayers() = 0;

	virtual void run() final;

	void pushLayer(Layer* value);

	const std::string& getName() const;

	const std::shared_ptr<Window>& getWindow() const;
private:
	std::shared_ptr<Window> window;

	std::string name;

	std::vector<Layer*> layers;

	bool running;
};
