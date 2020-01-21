#pragma once

#include <iostream>

#include <Engine/Engine.hpp>

#include <Game/Map/Map.hpp>
#include <Game/Map/Tile.hpp>

class TestLayer : public Layer
{
public:
    TestLayer() : Layer("TestLayer")
    {
        view = std::make_shared<View>(glm::ivec2(1280, 720));

        a = false;

        float vertices[] =
        {
                 0.5f,  0.5f,
                 0.5f, -0.5f,
                -0.5f, -0.5f,
                -0.5f,  0.5f,
        };

        unsigned int indices[] =
        {
            0, 1, 3,
            1, 2, 3
        };

        vao = std::make_shared<VertexArray>();

        std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
        vbo->setLayout(VertexLayout({
            VertexAttribute("position", GLDataType::Float2)
        }));

        std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(indices, 6);

        vao->setIndexBuffer(ibo);
        vao->setVertexBuffer(vbo);

        shader = std::make_shared<Shader>("Assets\\Shaders\\TestVert.glsl", "Assets\\Shaders\\TestFrag.glsl");

        map = std::make_shared<Map>(glm::ivec2(1920, 1080));

        std::clog << map->getSize().x * map->getSize().y << std::endl;

        auto tile = map->getTile(glm::ivec3(0, 0, 0));

        auto b = map->getNeighbors(tile);

        std::cout << b.size() << std::endl;

        std::clog << tile->getCoordinates().x << " " << tile->getCoordinates().y << " " << tile->getCoordinates().z << std::endl;
        for (auto t : b)
        {
            std::clog << t->getCoordinates().x << " " << t->getCoordinates().y << " " << t->getCoordinates().z << std::endl;
        }
    }

    virtual void update() override
    {
        a = Mouse::getButtonState(GLFW_MOUSE_BUTTON_LEFT);
    }

	virtual void render() override
	{
        if (a)
        {
            shader->bind();
            shader->setMat4("view", view->getMatrix());
            shader->setMat4("transform", glm::scale(glm::mat4(1.f), glm::vec3(glm::vec2(50.f, 50.f), 1.f)));
            vao->bind();
            glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
            vao->unbind();
            shader->unbind();
        }
	}
private:
    std::shared_ptr<View> view;
    std::shared_ptr<VertexArray> vao;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Map> map;
    bool a;
};

class Game : public Application
{
public:
	Game() : Application(std::string("Game"), glm::ivec2(1280, 720))
	{
		this->getWindow()->setVSync(false);
	}

	virtual void pushingLayers() override
	{
		pushLayer(new TestLayer);
	}
};
