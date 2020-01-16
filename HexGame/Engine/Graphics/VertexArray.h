#pragma once
#include "VertexBuffer.h"

class VertexLayout;

class VertexArray
{
private:
	unsigned int id;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& VB, const VertexLayout& layout);

	void Bind() const;
	void Unbind() const;
};