#pragma once

#include <map>

#include <Engine/Engine.hpp>

#include <Engine/Core/Manager.hpp>

class Button : Transformable
{
public:
	Button(const glm::vec2& pos, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, const std::string& name);

	bool contains(const glm::vec2& point) const;

	const std::shared_ptr<Texture>& getTexture() const;
	void setTexture(const std::shared_ptr<Texture>& value);

	const std::string& getName() const;
private:
	std::shared_ptr<Texture> texture;

	std::string name;
};

class ButtonsLayer : public Layer
{
public:
	ButtonsLayer();

	const std::shared_ptr<Button>& getButton(const std::string& name) const;

	virtual void update() override;
private:
	std::vector<std::shared_ptr<Button>> buttons;

	std::shared_ptr<View> view;
};

