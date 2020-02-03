#include <Game/Layers/MapLayer.hpp>

#include <Engine/Core/Manager.hpp>
#include <Engine/Graphics/Texture.hpp>

#include <Game/Map/Map.hpp>
#include <Game/Map/Tile.hpp>
#include <Game/Map/TerrainType.hpp>
#include <Game/Map/HexUtils.hpp>

MapLayer::MapLayer(const std::shared_ptr<Map>& map) :
	Layer("MapLayer"),
	map(map)
{
	view = std::make_shared<View>(glm::ivec2(1280, 720));

	TextureManager::add("orange", std::make_shared<Texture>("Assets\\Textures\\orange.png", ColorModel::RGBA));
	TextureManager::add("blue", std::make_shared<Texture>("Assets\\Textures\\blue.png", ColorModel::RGBA));
	TextureManager::add("grey", std::make_shared<Texture>("Assets\\Textures\\grey.png", ColorModel::RGBA));
	TextureManager::add("factory", std::make_shared<Texture>("Assets\\Textures\\Buildings\\factory.png", ColorModel::RGBA));

	float vertices[] =
	{
		.5f,  .5f, 1.f, 0.f,
		.5f, -.5f, 1.f, 1.f,
		-.5f, -.5f, 0.f,1.f,
		-.5f,  .5f, 0.f, 0.f
	};

	unsigned int indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	vao = std::make_shared<VertexArray>();

	std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
	vbo->setLayout(VertexLayout({
		VertexAttribute("position", GLDataType::Float2),
		VertexAttribute("1", GLDataType::Float2)
		}));

	std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(indices, 6);

	vao->setIndexBuffer(ibo);
	vao->setVertexBuffer(vbo);

	treasuryMoney = 500;

	ShaderManager::add("Texture", std::make_shared<Shader>("Assets\\Shaders\\TextureVert.glsl", "Assets\\Shaders\\TextureFrag.glsl"));

	double lastTime = glfwGetTime();		// Debug
}

void MapLayer::update()
{
	if (Keyboard::isKeyPressed(GLFW_KEY_W))
		speed += 1.f;

	if (Keyboard::isKeyPressed(GLFW_KEY_S))
		speed -= 1.f;

	if (Keyboard::getKeyState(GLFW_KEY_UP))
		view->move({ 0.f, speed });

	if (Keyboard::getKeyState(GLFW_KEY_DOWN))
		view->move({ 0.f, -speed });

	if (Keyboard::getKeyState(GLFW_KEY_LEFT))
		view->move({ -speed, 0.f });

	if (Keyboard::getKeyState(GLFW_KEY_RIGHT))
		view->move({ speed, 0.f });

	if (Keyboard::getKeyState(GLFW_KEY_Y))
		view->setScale(view->getScale() + 0.1f);

	if (Keyboard::getKeyState(GLFW_KEY_H))
		view->setScale(view->getScale() - 0.1f);

	auto pos = Mouse::getCoordinates();

	glm::vec2 p(glm::unProject(glm::vec3{ pos, 1.f }, glm::mat4(1.f), view->getMatrix(), glm::vec4(0.f, 0.f, 1280.f, 720.f)));


	// Update
	totalUpkeep = 0;

	for (auto i : buildings)
	{
		i->update();
		totalUpkeep += i->getUpkeep();
	}

	if (treasuryMoney > 0) treasuryMoney -= totalUpkeep;

	// Building Сonstruction
	if (Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		auto tiles = map->getTiles();

		for (auto tile : tiles)
			if (tile->contains(p))
			{
				buildings.push_back(std::make_shared<Sawmill>(tile));
				treasuryMoney -= buildings.back()->getBuildingCost();				// Костыль?
			}
	}

	// Debug
	double currentTime = glfwGetTime();
	if (currentTime - lastTime >= 1.0)
	{
		int number = 0;

		std::cout << std::endl;

		std::cout << "Treasury Money: " << round(treasuryMoney) << " coins" << std::endl;
		std::cout << "Upkeep: " << round(totalUpkeep * 3600) << " coins / minute" << std::endl;

		for (auto i : buildings)
		{
			std::cout << "Building " << number << ": ";
			std::cout << "RawWood: " << i->getResourseAmount(ResourseType::RawWood)
					  << ", ProcessedWood: " << i->getResourseAmount(ResourseType::ProcessedWood)
					  << ", Planks: " << i->getResourseAmount(ResourseType::Plank) << std::endl;
			
			number++;
		}

		lastTime += 1;

		std::cout << std::endl;
	}
}

void MapLayer::render()
{
	// колхозный рендер
	auto shader = ShaderManager::get("Texture");
	shader->bind();
	shader->setInt("ourTexture", 0);
	shader->setMat4("view", view->getMatrix());
	vao->bind();

	auto tiles = map->getTiles();
	for (const std::shared_ptr<Tile>& tile : tiles)
	{
		switch (tile->getTerrainType())
		{
		case TerrainType::Flatland:
			TextureManager::get("blue")->bind();
			break;
		case TerrainType::Hill:
			TextureManager::get("orange")->bind();
			break;
		case TerrainType::Mountain:
			TextureManager::get("grey")->bind();
			break;
		}

		shader->setMat4("transform", tile->getTransform());

		glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
	}

	for (auto i : buildings)
	{
		shader->setMat4("transform", i->getTransform());

		TextureManager::get("factory")->bind();

		glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
	}

	vao->unbind();
	shader->unbind();
}