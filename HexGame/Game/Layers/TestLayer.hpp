#pragma once

#include <Engine/Engine.hpp>

#include <vector>

#include <Engine/Graphics/Renderer/Renderable.hpp>
#include <Engine/Graphics/Renderer/Batch.hpp>


float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

class TestLayer : public Layer
{
public:
	TestLayer() : Layer("TestLayer")
	{
		view = std::make_shared<View>(glm::ivec2(1280, 720));
		batch = std::make_shared<Batch>(this->getName(), view);
		batch->setShader(std::make_shared<Shader>("Assets\\Shaders\\BatchVert.glsl", "Assets\\Shaders\\BatchFrag.glsl"));
		batch->setTexture(std::make_shared<Texture>("Assets\\Textures\\Landscape\\Landscape.png", ColorModel::RGBA, TextureFilter::Linear));

		const std::vector<glm::vec2>& uv = { glm::vec2(0.f, .5f), glm::vec2(0.f, 0.f), glm::vec2(.5f, 0.f), glm::vec2(.5f, .5f) };
		for (int x = 0; x < 18; x++)
			for (int y = 0; y < 10; y++)
				batch->submit(std::make_shared<Renderable>(glm::vec2(((float)x + (float)y / 2) * 0.9f * 120.f, (float)y * 0.9f * 0.86f * 120.f), glm::vec2(120.f), uv, glm::vec4(1.f)));
	}

	virtual void update() override
	{
		float speed = 30.f;

		if (Keyboard::getKeyState(GLFW_KEY_W))
			view->move({ 0.f, speed });

		if (Keyboard::getKeyState(GLFW_KEY_S))
			view->move({ 0.f, -speed });

		if (Keyboard::getKeyState(GLFW_KEY_A))
			view->move({ -speed, 0.f });

		if (Keyboard::getKeyState(GLFW_KEY_D))
			view->move({ speed, 0.f });

		if (Keyboard::getKeyState(GLFW_KEY_Q))
			view->setScale(view->getScale() + 0.1f);

		if (Keyboard::getKeyState(GLFW_KEY_E))
			view->setScale(view->getScale() - 0.1f);
	}

	virtual void render() override
	{
		batch->begin();
		batch->render();
		batch->end();
	}
private:
	std::shared_ptr<Batch> batch;
	std::shared_ptr<View> view;
	int i = 0;
};
