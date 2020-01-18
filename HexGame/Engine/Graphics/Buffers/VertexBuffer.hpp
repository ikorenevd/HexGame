#pragma once

#include <memory>

#include <Engine/Core/OpenGL.hpp>

#include <Engine/Graphics/Buffers/VertexLayout.hpp>

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void setLayout(const VertexLayout& value);
	const VertexLayout& getLayout() const;

	unsigned int getId() const;

	void bind();
	void unbind();
private:
	unsigned int id;

	VertexLayout layout;
};