#pragma once

#include <iostream>

#include <Engine/Engine.hpp>

class TestLayer : public Layer
{
public:
	TestLayer() : Layer("TestLayer")
	{
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
        
        unsigned int vbo, ibo;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ibo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        shader = std::make_shared<Shader>("Assets\\Shaders\\TestVert.glsl", "Assets\\Shaders\\TestFrag.glsl");
	}

	virtual void render() override
	{
        shader->bind();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        shader->unbind();
	}
private:
	unsigned int vao;
    std::shared_ptr<Shader> shader;
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
