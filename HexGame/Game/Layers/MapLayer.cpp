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
	TextureManager::add("Hex", std::make_shared<Texture>("Assets\\Textures\\Hex\\Hex.png", ColorModel::RGBA));
	TextureManager::add("SelectedHex", std::make_shared<Texture>("Assets\\Textures\\Hex\\SelectedHex.png", ColorModel::RGBA));

	TextureManager::add("Flatland", std::make_shared<Texture>("Assets\\Textures\\Flatland.png", ColorModel::RGBA));
	TextureManager::add("Hill", std::make_shared<Texture>("Assets\\Textures\\Flatland.png", ColorModel::RGBA));
	TextureManager::add("Mountain", std::make_shared<Texture>("Assets\\Textures\\Flatland.png", ColorModel::RGBA));

	TextureManager::add("Factory", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Factory01.png", ColorModel::RGBA));
	TextureManager::add("Felled", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Factory01.png", ColorModel::RGBA));
	TextureManager::add("Mine", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Factory01.png", ColorModel::RGBA));

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
	buttonsGame.push_back(std::make_shared<Button>(glm::vec2(-viewUI->getSize().x / 2 * 0.925, viewUI->getSize().y / 2 * 0.875), glm::vec2(80, 80), TextureManager::get("Factory"), "Sawmill"));
	buttonsGame.push_back(std::make_shared<Button>(glm::vec2(-viewUI->getSize().x / 2 * 0.925, viewUI->getSize().y / 2 * 0.65), glm::vec2(80, 80), TextureManager::get("Felled"), "Felled"));
	buttonsGame.push_back(std::make_shared<Button>(glm::vec2(-viewUI->getSize().x / 2 * 0.925, viewUI->getSize().y / 2 * 0.425), glm::vec2(80, 80), TextureManager::get("Mine"), "Mine"));
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

	std::vector<std::shared_ptr<Tile>> allTiles = map->getTiles();
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
	for (auto button : buttonsGame)
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
			if (treasuryMoney - buttonsGame[0]->getBuildingCost() >= 0)
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

		for (int i = 0; i < 15; i++)
		{
			if (storageMap[(ResourseType)i] != 0) std::cout << "Map Storage: " << storageMap[(ResourseType)i] << std::endl;
		}

		std::cout << std::endl;
	}
}

void MapLayer::render()
{
	auto shader = ShaderManager::get("Texture");
	shader->bind();
	shader->setInt("ourTexture", 0);
	shader->setMat4("view", viewGame->getMatrix());
	vao->bind();

		// Карта
	// Отрисовка клеток
	std::vector<std::shared_ptr<Tile>> allTiles = map->getTiles();

	for (auto tile : allTiles)
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

	// Отрисовка обводки клеток
	for (auto tile : allTiles)
	{
		if (tile == selectedTile)
			TextureManager::get("SelectedHex")->bind();
		else
			TextureManager::get("Hex")->bind();

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

		// Интерфейс
	// Отрисовка кнопок
	bool tileFree = true;

	for (auto building : buildings)
	{
		if (building->getTile() == selectedTile)
		{
			tileFree = false;
			break;
		}
	}

	if (selectedTile == nullptr || tileFree)
	{
		// Без выделенной клетки
		shader->setMat4("view", viewUI->getMatrix());

		for (auto button : buttonsGame)
		{
			shader->setMat4("transform", button->getTransform());

			button->getTexture()->bind();

			glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
		}
	}
	else
	{
		// При выделенной клетке
		shader->setMat4("view", viewUI->getMatrix());

		for (auto button : buttonsUI)
		{
			shader->setMat4("transform", button->getTransform());

			button->getTexture()->bind();

			glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
		}
	}

	vao->unbind();
	shader->unbind();
}