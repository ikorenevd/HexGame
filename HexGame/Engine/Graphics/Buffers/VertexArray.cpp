#include <Engine/Graphics/Buffers/VertexArray.hpp>

#include <iostream>
#include <vector>

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

void VertexArray::bind()
{
	glBindVertexArray(id);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& value)
{
	glBindVertexArray(id);
	value->bind();

	const VertexLayout layout = value->getLayout();
	//const std::vector<VertexAttribute> attributes = layout.getAttributes();

	unsigned int index = 0;
	for (const auto& attribute : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(0, getGLDataTypeElementsCount(attribute.type), getGLDataTypeToBaseOpenGLType(attribute.type), attribute.normalized ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)attribute.offset);
		index++;
	}

	value->unbind();
	glBindVertexArray(0);

	vertexBuffer = value;
}

const std::shared_ptr<VertexBuffer>& VertexArray::getVertexBuffer() const
{
	return vertexBuffer;
}

void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& value)
{
	glBindVertexArray(id);
	value->bind();
	indexBuffer = value;
	//value->unbind();
	glBindVertexArray(0);
}

const std::shared_ptr<IndexBuffer>& VertexArray::getIndexBuffer() const
{
	return indexBuffer;
}

unsigned int VertexArray::getId() const
{
	return id;
}
