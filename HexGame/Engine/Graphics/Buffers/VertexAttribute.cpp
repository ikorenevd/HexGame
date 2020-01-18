#include <Engine/Graphics/Buffers/VertexAttribute.hpp>

VertexAttribute::VertexAttribute(const std::string& name, GLDataType type, bool normalized) :
	name(name),
	size(getGLDataTypeSize(type)),
	type(type),
	normalized(normalized),
	offset(0)
{
}

const std::string& VertexAttribute::getName() const
{
	return name;
}