#pragma once

#include <string>

#include <Engine/Core/OpenGL.hpp>

enum class ColorModel
{
	RGB = 0,
	RGBA
};

enum class TextureFilter
{
	Nearest = 0,
	Linear
};

class Texture
{
public:
	Texture(const std::string& path, ColorModel colMod, TextureFilter textFilter = TextureFilter::Nearest);

	void bind();
	void unbind();

	unsigned int getId() const;

	const glm::ivec2& getSize() const;
private:
	unsigned int id;

	glm::ivec2 size;
};
