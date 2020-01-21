
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

        texture = std::make_shared<Texture>("Assets\\Textures\\Flatland.png", ColorModel::RGBA);

        float vertices[] =
        {
            0.5f,  0.5f, 1.f, 1.f,
            0.5f, -0.5f, 1.f, 0.f,
            -0.5f, -0.5f, 0.f,0.f,
            -0.5f,  0.5f, 0.f, 1.f
        };

        unsigned int indices[] =
        {
            0, 1, 3,
            1, 2, 3
        };
        
        std::clog << sizeof(vertices) / 4 << std::endl;


        vao = std::make_shared<VertexArray>();

        std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
        vbo->setLayout(VertexLayout({
            VertexAttribute("position", GLDataType::Float2),
            VertexAttribute("1", GLDataType::Float2)
        }));

        std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(indices, 6);

        vao->setIndexBuffer(ibo);
        vao->setVertexBuffer(vbo);

        shader = std::make_shared<Shader>("Assets\\Shaders\\TextureVert.glsl", "Assets\\Shaders\\TextureFrag.glsl");
    }

    virtual void update() override
    {
        a = Mouse::getButtonState(GLFW_MOUSE_BUTTON_LEFT);
    }

	virtual void render() override
	{
        if (a)
        {
            texture->bind();
            shader->bind();
            shader->setInt("ourTexture", 0);
            shader->setMat4("view", view->getMatrix());
            shader->setMat4("transform", glm::scale(glm::mat4(1.f), glm::vec3(100, 100, 1)));
            vao->bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            vao->unbind();
            shader->unbind();
            texture->unbind();
        }
	}
private:
    std::shared_ptr<View> view;
    std::shared_ptr<VertexArray> vao;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Texture> texture;
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
		map = std::make_shared<Map>(glm::ivec2(100, 100));

        pushLayer(new TestLayer);
		//pushLayer(new MapLayer(map));
	}
private:
	std::shared_ptr<Map> map;
};
