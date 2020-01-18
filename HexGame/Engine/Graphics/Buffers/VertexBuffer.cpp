#include <Engine/Graphics/Buffers/VertexBuffer.hpp>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &id);
}

void VertexBuffer::setLayout(const VertexLayout& value)
{
	layout = value;
}

const VertexLayout& VertexBuffer::getLayout() const
{
	return layout;
}

unsigned int VertexBuffer::getId() const
{
	return id;
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}