#pragma once

#include <vector>
#include <initializer_list> // для того чтобы в конструктор передавать массив VertexAttrib

#include <Engine/Core/OpenGL.hpp>
#include <Engine/Graphics/GLDataType.hpp>
#include <Engine/Graphics/Buffers/VertexAttribute.hpp>

class VertexLayout
{
public:
	VertexLayout();

	VertexLayout(const std::initializer_list<VertexAttribute>& attributes);

	std::vector<VertexAttribute>::iterator begin();
	std::vector<VertexAttribute>::iterator end();
	std::vector<VertexAttribute>::const_iterator begin() const;
	std::vector<VertexAttribute>::const_iterator end() const;

	unsigned int getStride() const;
	const std::vector<VertexAttribute>& getAttributes() const;
private:
	void updateOffsetsAndStride();

	std::vector<VertexAttribute> attributes;
	unsigned int stride;
};
