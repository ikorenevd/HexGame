#pragma once

#include <Engine/Core/OpenGL.hpp>

#include <Engine/Graphics/Transformable.hpp>

class Updatable
{
public:
	virtual void update(const glm::vec2& mouseCoord)
	{};
};

class GameObject : public Updatable, public Transformable
{
public:
	virtual void update(const glm::vec2& mouseCoord)
	{
	};
};
