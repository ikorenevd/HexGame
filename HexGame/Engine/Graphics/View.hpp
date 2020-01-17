#pragma once

#include <Engine/Core/OpenGL.hpp>

#include <glm/gtc/matrix_transform.hpp>

class View
{
public:
	View();
	View(const glm::vec2& size);

	void setSize(const glm::vec2& value);
	const glm::vec2& getSize() const;

	void setCenter(const glm::vec2& value);
	const glm::vec2& getCenter() const;

	void move(const glm::vec2& offset);

	const glm::mat4& getMatrix() const;
private:
	glm::vec2 center;
	glm::vec2 size;

	mutable glm::mat4 matrix;

	mutable bool dirty;
};