#include <Engine/Graphics/Buffers/VertexLayout.hpp>
#include <Engine/Graphics/Buffers/VertexAttribute.hpp>

#include <iostream>

VertexLayout::VertexLayout() :
	stride(0)
{

}

VertexLayout::VertexLayout(const std::initializer_list<VertexAttribute>& attributes) :
	attributes(attributes),
	stride(0)
{
	updateOffsetsAndStride();
}

std::vector<VertexAttribute>::iterator VertexLayout::begin()
{
	return attributes.begin();
}

std::vector<VertexAttribute>::iterator VertexLayout::end()
{
	return attributes.end();
}

std::vector<VertexAttribute>::const_iterator VertexLayout::begin() const
{
	return attributes.begin();
}

std::vector<VertexAttribute>::const_iterator VertexLayout::end() const
{
	return attributes.end();
}

void VertexLayout::updateOffsetsAndStride()
{
	unsigned int offset = 0;
	stride = 0;
	for (auto& attribute : attributes)
	{
		attribute.offset = offset;
		offset += attribute.size;
		stride += attribute.size;
	}
}

unsigned int VertexLayout::getStride() const
{
	return stride;
}

const std::vector<VertexAttribute>& VertexLayout::getAttributes() const
{
	return attributes;
}
