#pragma once

#include <Engine/Core/OpenGL.hpp>

#include <Engine/Graphics/Transformable.hpp>

class GameObject : public Transformable
{
public:
	virtual void update()
	{
	};
};
