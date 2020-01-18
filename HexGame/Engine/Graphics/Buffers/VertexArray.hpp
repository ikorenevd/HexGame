#pragma once

#include <Engine/Graphics/Buffers/VertexBuffer.hpp>
#include <Engine/Graphics/Buffers/IndexBuffer.hpp>
#include <Engine/Graphics/Buffers/VertexAttribute.hpp>

#include <memory>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind();
	void unbind();

	void setVertexBuffer(const std::shared_ptr<VertexBuffer>& value);
	const std::shared_ptr<VertexBuffer>& getVertexBuffer() const;

	void setIndexBuffer(const std::shared_ptr<IndexBuffer>& value);
	const std::shared_ptr<IndexBuffer>& getIndexBuffer() const;

	unsigned int getId() const;
private:
	unsigned int id;

	std::shared_ptr<VertexBuffer> vertexBuffer;
	std::shared_ptr<IndexBuffer> indexBuffer;
};
