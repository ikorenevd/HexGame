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
	viewGame = std::make_shared<View>(glm::ivec2(1280, 720));
	viewGame->move({ 800, 800 });
	viewGame->setScale(1.5);

	viewUI = std::make_shared<View>(glm::ivec2(1280, 720));

	// Текстуры
	TextureManager::add("Flatland", std::make_shared<Texture>("Assets\\Textures\\Hex.png", ColorModel::RGBA));
	TextureManager::add("Hill", std::make_shared<Texture>("Assets\\Textures\\Hex.png", ColorModel::RGBA));
	TextureManager::add("Mountain", std::make_shared<Texture>("Assets\\Textures\\Hex.png", ColorModel::RGBA));
	TextureManager::add("factory", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Factory01.png", ColorModel::RGBA));
	TextureManager::add("felled", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Factory01.png", ColorModel::RGBA));
	TextureManager::add("mine", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Factory01.png", ColorModel::RGBA));

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
	buttons.push_back(std::make_shared<Button>(glm::vec2(-viewUI->getSize().x / 2 * 0.8, -viewUI->getSize().y / 2 * 0.8), glm::vec2(100, 100), TextureManager::get("factory"), "Sawmill"));
	buttons.push_back(std::make_shared<Button>(glm::vec2(-viewUI->getSize().x / 2 * 0.6, -viewUI->getSize().y / 2 * 0.8), glm::vec2(100, 100), TextureManager::get("felled"), "Felled"));
	buttons.push_back(std::make_shared<Button>(glm::vec2(-viewUI->getSize().x / 2 * 0.4, -viewUI->getSize().y / 2 * 0.8), glm::vec2(100, 100), TextureManager::get("mine"), "Mine"));
}

void MapLayer::update()
{
	// Взаимодействие пользователя с программой
	if (Keyboard::isKeyPressed(GLFW_KEY_W))
		speed += 1.f;

	if (Keyboard::isKeyPressed(GLFW_KEY_S))
		speed -= 1.f;

	if (Keyboard::getKeyState(GLFW_KEY_UP))
		viewGame->move({ 0.f, speed });

	if (Keyboard::getKeyState(GLFW_KEY_DOWN))
		viewGame->move({ 0.f, -speed });

	if (Keyboard::getKeyState(GLFW_KEY_LEFT))
		viewGame->move({ -speed, 0.f });

	if (Keyboard::getKeyState(GLFW_KEY_RIGHT))
		viewGame->move({ speed, 0.f });

	if (Keyboard::getKeyState(GLFW_KEY_Y))
		viewGame->setScale(viewGame->getScale() + 0.1f);

	if (Keyboard::getKeyState(GLFW_KEY_H))
		viewGame->setScale(viewGame->getScale() - 0.1f);

	// Переменные
	glm::vec2 mousePosition = Mouse::getCoordinates();			// Корень, поясни, что это. Пора готовиться к защите
	glm::vec2 cursorGame(glm::unProject(glm::vec3{ mousePosition, 1.f }, glm::mat4(1.f), viewGame->getMatrix(), glm::vec4(0.f, 0.f, 1280.f, 720.f)));
	glm::vec2 cursorUI(glm::unProject(glm::vec3{ mousePosition, 1.f }, glm::mat4(1.f), viewUI->getMatrix(), glm::vec4(0.f, 0.f, 1280.f, 720.f)));

	auto allTiles = map->getTiles();
	bool debug = false;

	// Обновление состояние зданий, общей стоимости их содержания и казны города
	totalUpkeep = 0;

	for (auto building : buildings)
	{
		building->update();

		if (!building->isFrozen() and building->isFunctioning())
			totalUpkeep += building->getUpkeep();
		else
			totalUpkeep += building->getUpkeep() / 5;
	}

	treasuryMoney -= totalUpkeep;

	// Отключение зданий при пустой казне
	if (treasuryMoney <= 0 && !treasuryEmpty)
	{
		treasuryEmpty = true;

		for (auto building : buildings)
			building->setFrozen(true);
	}

	// Включение зданий при положительной казне
	if (treasuryMoney > 0 && treasuryEmpty)
	{
		treasuryEmpty = false;

		for (auto building : buildings)
			building->setFrozen(false);
	}

	// Расчет общих ресурсов карты
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

		debug = true;		// Debug
		lastTime++;
	}

	// Кнопки
	for (auto button : buttons)
	{
		if (button->contains(cursorUI) && Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			selectedBuilding = button;
	}

	// Выделение клетки
	if (Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		for (auto tile : allTiles)
		{
			if (tile->contains(cursorGame))
			{
				if (selectedTile != tile || selectedTile == nullptr)
					selectedTile = tile;
				else
					selectedTile = nullptr;

				selectedBuilding = nullptr;
			}
		}
	}

	// Постройка зданий
	if (selectedTile != nullptr && selectedBuilding != nullptr)
	{
		bool tileUsed = false;
		for (auto building : buildings)
		{
			if (building->getTile() == selectedTile)
			{
				tileUsed = true;
				break;
			}
		}

		if (!tileUsed)
			if (treasuryMoney - buttons[0]->getBuildingCost() >= 0)
			{
				buildings.push_back(selectedBuilding->buildBuilding(selectedTile));
				std::cout << "---Building is built.   ";

				treasuryMoney -= selectedBuilding->getBuildingCost();

				selectedBuilding = nullptr;
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

	for (auto tile : allTiles)
	{
		//tile->setTerrainType(TerrainType::Flatland);

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
	shader->setMat4("view", viewGame->getMatrix());
	vao->bind();

	// Отрисовка клеток
	auto tiles = map->getTiles();
	for (const std::shared_ptr<Tile>& tile : tiles)
	{
		switch (tile->getTerrainType())
		{
		case TerrainType::Flatland:
			TextureManager::get("Flatland")->bind();
			break;
		case TerrainType::Hill:
			TextureManager::get("Hill")->bind();
			break;
		case TerrainType::Mountain:
			TextureManager::get("Mountain")->bind();
			break;
		}

		shader->setMat4("transform", tile->getTransform());

		glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
	}

	// Отрисовка зданий
	for (auto building : buildings)
	{
		shader->setMat4("transform", building->getTransform());

		building->getTexture()->bind();

		glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
	}

	// Отрисовка кнопок
	shader->setMat4("view", viewUI->getMatrix());

	for (auto button : buttons)
	{
		shader->setMat4("transform", button->getTransform());

		button->getTexture()->bind();

		glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
	}

	vao->unbind();
	shader->unbind();
}