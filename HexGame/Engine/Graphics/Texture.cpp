#include <Engine/Graphics/Texture.hpp>

#include <iostream>

Texture::Texture(const std::string& path, ColorModel colMod, TextureFilter textFilter)
{
	glGenTextures(1, &id);
	bind();

	switch (textFilter)
	{
	case TextureFilter::Nearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case TextureFilter::Linear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}

	switch (colMod)
	{
	case ColorModel::RGB:
		unsigned char* image;
		image = SOIL_load_image(path.c_str(), &size.x, &size.y, 0, SOIL_LOAD_RGB);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		
		SOIL_free_image_data(image);
		break;
	case ColorModel::RGBA:
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//unsigned char* image;
		image = SOIL_load_image(path.c_str(), &size.x, &size.y, 0, SOIL_LOAD_RGBA);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		
		SOIL_free_image_data(image);
		break;
	}

	unbind();
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::getId() const
{
	return id;
}

const glm::ivec2& Texture::getSize() const
{
	return size;
}
