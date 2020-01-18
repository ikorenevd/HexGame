#pragma once

#include <iostream>

#include <Engine/Engine.hpp>

class TestLayer : public Layer
{
public:
    TestLayer() : Layer("TestLayer")
    {
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

        //unsigned int vbo, ibo;

        //glGenVertexArrays(1, &vao);
        //glGenBuffers(1, &vbo);
        //glGenBuffers(1, &ibo);

        //glBindVertexArray(vao);

        //glBindBuffer(GL_ARRAY_BUFFER, vbo);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        //glEnableVertexAttribArray(0);
        //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        //glBindVertexArray(0);

        vao = std::make_shared<VertexArray>();

        std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
        vbo->setLayout(VertexLayout({
            VertexAttribute("position", GLDataType::Float2)
        }));

        std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(indices, 6);

        vao->setIndexBuffer(ibo);
        vao->setVertexBuffer(vbo);

        shader = std::make_shared<Shader>("Assets\\Shaders\\TestVert.glsl", "Assets\\Shaders\\TestFrag.glsl");
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
            vao->bind();
            glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
            vao->unbind();
            shader->unbind();
            //shader->bind();
            //glBindVertexArray(vao);
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            //glBindVertexArray(0);
            //shader->unbind();
        }
	}
private:
	//unsigned int vao;
    std::shared_ptr<VertexArray> vao;
    std::shared_ptr<Shader> shader;
    bool a;
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
