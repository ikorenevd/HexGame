#pragma once

#include <vector>

#include <Engine/Core/OpenGL.hpp>
#include <Engine/Graphics/Transformable.hpp>

class Renderable : public Transformable
{
public:
	Renderable(const glm::vec2& pos, const glm::vec2& scale, const std::vector<glm::vec2>& uv = {glm::vec2(0.f, 1.f), glm::vec2(0.f, 0.f), glm::vec2(1.f, 0.f), glm::vec2(1.f, 1.f)}, const glm::vec4& color = glm::vec4(1.f, 1.f, 1.f, 1.f));

	void setColor(const glm::vec4& value);
	const glm::vec4& getColor() const;

	void setUV(const std::vector<glm::vec2>& value);
	const std::vector<glm::vec2>& getUV() const;
private:
	glm::vec4 color;

	std::vector<glm::vec2> uv;
};

