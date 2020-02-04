#include <Game/Layers/ButtonsLayer.hpp>

Button::Button(const glm::vec2& pos, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, const std::string& name) :
	Transformable(pos, scale),
	texture(texture),
	name(name)
{
}

const std::shared_ptr<Texture>& Button::getTexture() const
{
	return texture;
}

void Button::setTexture(const std::shared_ptr<Texture>& value)
{
	texture = value;
}

bool Button::contains(const glm::vec2& point) const
{
	auto pos = getPosition();
	auto size = getScale();

	if ((pos.x + size.x) >= point.x &&
		(pos.x - size.x) <= point.x &&
		(pos.y + size.y) >= point.y &&
		(pos.y - size.y) <= point.y)
	{
		return true;
	};

	return false;
}

const std::string& Button::getName() const
{
	return name;
}

ButtonsLayer::ButtonsLayer() :
	Layer("ButtonsLayer"),
	view(std::make_shared<View>(glm::ivec2(1280, 720)))
{
	TextureManager::add("mine", std::make_shared<Texture>("Assets\\Textures\\mine.png", ColorModel::RGBA));

	buttons.push_back(std::make_shared<Button>(glm::vec2(100, 100), glm::vec2(50, 40), TextureManager::get("mine"), "mine"));
}

void ButtonsLayer::update()
{
	auto p = glm::vec2(glm::unProject(glm::vec3(Mouse::getCoordinates().x, Mouse::getCoordinates().y, 1.f ), glm::mat4(1.f), view->getMatrix(), glm::vec4(0.f, 0.f, 1280.f, 720.f)));

	for (auto btn : buttons)
	{
		if (btn->contains(p))
		{
			std::cout << "pick" << std::endl;
		}
	}
}

const std::shared_ptr<Button>& ButtonsLayer::getButton(const std::string& name) const
{
	for (auto btn : buttons)
		if (btn->getName() == name)
			return btn;

	return nullptr;
}
