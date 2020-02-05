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
	buttonView = std::make_shared<View>(glm::ivec2(1280, 720));

	TextureManager::add("orange", std::make_shared<Texture>("Assets\\Textures\\orange.png", ColorModel::RGBA));
	TextureManager::add("blue", std::make_shared<Texture>("Assets\\Textures\\blue.png", ColorModel::RGBA));
	TextureManager::add("grey", std::make_shared<Texture>("Assets\\Textures\\grey.png", ColorModel::RGBA));
	TextureManager::add("factory", std::make_shared<Texture>("Assets\\Textures\\Buildings\\factory.png", ColorModel::RGBA));
	TextureManager::add("felled", std::make_shared<Texture>("Assets\\Textures\\Buildings\\felled.png", ColorModel::RGBA));
	TextureManager::add("mine", std::make_shared<Texture>("Assets\\Textures\\Buildings\\mine.png", ColorModel::RGBA));

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

	treasuryMoney = 1750;

	ShaderManager::add("Texture", std::make_shared<Shader>("Assets\\Shaders\\TextureVert.glsl", "Assets\\Shaders\\TextureFrag.glsl"));

	double lastTime = glfwGetTime();

	// Кнопки
	buttons.push_back(std::make_shared<Button>(glm::vec2(-buttonView->getSize().x / 2 * 0.8, -buttonView->getSize().y / 2 * 0.8), glm::vec2(100, 100), TextureManager::get("factory"), "Sawmill"));
	buttons.push_back(std::make_shared<Button>(glm::vec2(-buttonView->getSize().x / 2 * 0.6, -buttonView->getSize().y / 2 * 0.8), glm::vec2(100, 100), TextureManager::get("felled"), "Felled"));
	buttons.push_back(std::make_shared<Button>(glm::vec2(-buttonView->getSize().x / 2 * 0.4, -buttonView->getSize().y / 2 * 0.8), glm::vec2(100, 100), TextureManager::get("mine"), "Mine"));
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


	// Переменные
	auto pos = Mouse::getCoordinates();
	auto tiles = map->getTiles();
	glm::vec2 p(glm::unProject(glm::vec3{ pos, 1.f }, glm::mat4(1.f), view->getMatrix(), glm::vec4(0.f, 0.f, 1280.f, 720.f)));
	bool debug = false;

	// Кнопки
	for (auto button : buttons)
	{
		if (button->contains(p) && Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			waitingBuilding = true;
			pressedButton = button;
		}
	}

	// Обновление состояние зданий, общей стоимости их содержания и казны города
	totalUpkeep = 0;
	for (auto i : buildings)
	{
		i->update();

		if (!i->isFrozen() and i->isFunctioning())
			totalUpkeep += i->getUpkeep();
		else
			totalUpkeep += i->getUpkeep() / 5;
	}
	treasuryMoney -= totalUpkeep;

	// Отключение зданий при пустой казне
	if (treasuryMoney <= 0)		
		for (auto i : buildings)
			i->setFrozen(true);

	// Постройка зданий
	if (selectedTile != nullptr && waitingBuilding)
	{
		bool exit = false;
		for (auto building : buildings)
		{
			exit = (building->getTile()->getCoordinates() == selectedTile->getCoordinates());
			if (exit)
				break;
		}

		if (!exit)
			if (treasuryMoney - buttons[0]->getBuildingCost() >= 0)
			{
				buildings.push_back(pressedButton->buildBuilding(selectedTile));
				std::cout << "---Building is built.   ";

				treasuryMoney -= pressedButton->getBuildingCost();

				waitingBuilding = false;
				pressedButton;
			}
	}

	// Выделение клетки
	if (Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		for (auto tile : tiles)
		{
			if (tile->contains(p))
			{
				if (selectedTile != tile || selectedTile == nullptr)
					selectedTile = tile;
				else
					selectedTile = nullptr;
			}
		}
	}

	// Снос здания
	if (Keyboard::isKeyPressed(GLFW_KEY_DELETE) && selectedTile != nullptr)
	{
		int i = 0;

		for (auto building : buildings)
		{
			if (building->getTile() == selectedTile)
			{
				buildings.erase(buildings.begin() + i);
				break;
			}

			i++;
		}
	}

	// Общие ресурсы карты
	if (glfwGetTime() - lastTime >= 1)
	{
		storageMap = {};

		for (std::shared_ptr<Building> building : buildings)
		{
			for (int i = 0; i < 15; i++)
			{
				storageMap[(ResourseType)i] += building->getResourseAmount((ResourseType)i);
			}
		}

		debug = true;
		lastTime += 1;
	}

	// Debug
	if (debug)
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

		for (int i = 0; i < 15; i++)
		{
			if (storageMap[(ResourseType)i] != 0) std::cout << "Map Storage: " << storageMap[(ResourseType)i] << std::endl;
		}

		std::cout << std::endl;
	}

	// Подсветка выделенной клетки
	for (auto tile : tiles)
	{
		tile->setTerrainType(TerrainType::Flatland);

		if (selectedTile != nullptr)
			selectedTile->setTerrainType(TerrainType::Hill);
	}
}

void MapLayer::render()
{
	// Колхозный рендер
	auto shader = ShaderManager::get("Texture");
	shader->bind();
	shader->setInt("ourTexture", 0);
	shader->setMat4("view", view->getMatrix());
	vao->bind();

	// Отрисовка клеток
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

	// Отрисовка зданий
	for (auto i : buildings)
	{
		shader->setMat4("transform", i->getTransform());

		i->getTexture()->bind();

		glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
	}

	// Кнопки
	shader->setMat4("view", buttonView->getMatrix());

	for (auto i : buttons)
	{
		shader->setMat4("transform", i->getTransform());

		i->getTexture()->bind();

		glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
	}

	vao->unbind();
	shader->unbind();
}