#pragma once

#include <Engine/Core/OpenGL.hpp>

class Transformable
{
public:
	Transformable(const glm::vec2& position = glm::vec2(0.f, 0.f), const glm::vec2& scale = glm::vec2(1.f, 1.f));

	void move(const glm::vec2& offset);
	void setPosition(const glm::vec2& value);

	const glm::vec2& getPosition() const;

	void setScale(const glm::vec2& value);

	const glm::vec2& getScale() const;

	const glm::mat4& getTransform() const;

	virtual bool contains(const glm::vec2& point) const; // must be override
private:
	mutable glm::mat4 matrix;

	glm::vec2 position;
	glm::vec2 scale;

	mutable bool dirty;
};
