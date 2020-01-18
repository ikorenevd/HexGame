#pragma once

#include <Engine/Core/OpenGL.hpp>

class IndexBuffer
{
public:
	IndexBuffer(unsigned int* data, int count);
	~IndexBuffer();

	void bind();
	void unbind();

	unsigned int getId() const;
	int getCount() const;
private:
	unsigned int id;
	int count;
};