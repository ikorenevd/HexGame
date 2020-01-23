#pragma once

#include <Engine/Engine.hpp>

class Map;

class MapLayer : public Layer
{
public:
	MapLayer(const std::shared_ptr<Map>& map);

	virtual void update() override;
	virtual void render() override;
private:
	std::shared_ptr<Map> map;

	std::shared_ptr<View> view;
	float speed = 2.f;

	std::shared_ptr<VertexArray> vao;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> orange;
	std::shared_ptr<Texture> blue;
	std::shared_ptr<Texture> grey;
};
