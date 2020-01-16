#pragma once

class IndexBuffer
{
private:
	unsigned int id, count;

public:
	IndexBuffer(unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind();
	void Unbind();
};