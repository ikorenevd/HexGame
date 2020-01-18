#pragma once

#include <string>

#include <Engine/Core/OpenGL.hpp>
#include <Engine/Graphics/GLDataType.hpp>

class VertexAttribute
{
public:
	VertexAttribute() = default;

	VertexAttribute(const std::string& name, GLDataType type, bool normalized = false);

	const std::string& getName() const;

	int size;
	GLDataType type;
	bool normalized;
	int offset;
private:
	std::string name;
};
