#include <Engine/Graphics/Renderer/Renderable.hpp>

Renderable::Renderable(const glm::vec2& pos, const glm::vec2& scale, const std::vector<glm::vec2>& uv, const glm::vec4& color) :
	Transformable(pos, scale),
	uv(uv),
	color(color)
{
}

void Renderable::setColor(const glm::vec4& value)
{
	color = value;
}

const glm::vec4& Renderable::getColor() const
{
	return color;
}

void Renderable::setUV(const std::vector<glm::vec2>& value)
{
	uv = value;
}

const std::vector<glm::vec2>& Renderable::getUV() const
{
	return uv;
}
