#include <Engine/Graphics/Transformable.hpp>

#include <glm/gtc/matrix_transform.hpp>

Transformable::Transformable(const glm::vec2& position, const glm::vec2& scale) :
	matrix(glm::mat4(1.f)),
	position(position),
	scale(scale),
	dirty(true)
{
}

void Transformable::move(const glm::vec2& offset)
{
	position += offset;

	dirty = true;
}

void Transformable::setPosition(const glm::vec2& value)
{
	position = value;

	dirty = true;
}

const glm::vec2& Transformable::getPosition() const
{
	return position;
}

void Transformable::setScale(const glm::vec2& value)
{
	scale = value;

	dirty = true;
}

const glm::vec2& Transformable::getScale() const
{
	return scale;
}

const glm::mat4& Transformable::getTransform() const
{
	if (dirty)
	{
		// recalculate matrix
		matrix = glm::scale(glm::translate(glm::mat4(1.f), glm::vec3(position, 0.f)), glm::vec3(scale, 1.f));

		dirty = false;
	}

	return matrix;
}

bool Transformable::contains(const glm::vec2& point) const
{
	return false;
}
