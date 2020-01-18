#include <Engine/Core/OpenGL.hpp>

#include <Engine/Graphics/Buffers/IndexBuffer.hpp>

IndexBuffer::IndexBuffer(unsigned int* data, int count) :
	id(0),
	count(count)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &id);
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getId() const
{
	return id;
}

int IndexBuffer::getCount() const
{
	return count;
}
