#include <Game/Layers/MapLayer.hpp>

#include <Engine/Core/Manager.hpp>
#include <Engine/Graphics/Texture.hpp>

#include <Game/Map/Map.hpp>
#include <Game/Map/Tile.hpp>
#include <Game/Map/TerrainType.hpp>
#include <Game/Map/HexUtils.hpp>

MapLayer::MapLayer(const std::shared_ptr<Map>& map) :
	Layer("MapLayer"),
	map(map),
	speed(6.f)
{
	viewGame = std::make_shared<View>(glm::ivec2(1280, 720));
	viewGame->move({ 200, 200 });

	viewUI = std::make_shared<View>(glm::ivec2(1280, 720));

	// Текстуры
	TextureManager::add("Paper", std::make_shared<Texture>("Assets\\Textures\\Paper.png", ColorModel::RGBA));

	TextureManager::add("Hex", std::make_shared<Texture>("Assets\\Textures\\Hex\\Hex.png", ColorModel::RGBA));
	TextureManager::add("PointedHex", std::make_shared<Texture>("Assets\\Textures\\Hex\\PointedHex.png", ColorModel::RGBA));
	TextureManager::add("SelectedHex", std::make_shared<Texture>("Assets\\Textures\\Hex\\SelectedHex.png", ColorModel::RGBA));
	TextureManager::add("SelectedTransportHex", std::make_shared<Texture>("Assets\\Textures\\Hex\\TransportingHex.png", ColorModel::RGBA));

	TextureManager::add("Flatland", std::make_shared<Texture>("Assets\\Textures\\Landscape\\Flatland.png", ColorModel::RGBA));
	TextureManager::add("Hill", std::make_shared<Texture>("Assets\\Textures\\Landscape\\Hill.png", ColorModel::RGBA));
	TextureManager::add("Mountain", std::make_shared<Texture>("Assets\\Textures\\Landscape\\Mountain.png", ColorModel::RGBA));
	TextureManager::add("Forest", std::make_shared<Texture>("Assets\\Textures\\Landscape\\Forest.png", ColorModel::RGBA));

	TextureManager::add("Sawmill", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Sawmill.png", ColorModel::RGBA));
	TextureManager::add("Felled", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Felled.png", ColorModel::RGBA));
	TextureManager::add("Mine", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Mine.png", ColorModel::RGBA));
	TextureManager::add("Warehouse", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Warehouse.png", ColorModel::RGBA));

	float vertices[] =
	{
		-0.5f, -0.5f,  0.f, 1.f,
		-0.5f,  0.5f,  0.f, 0.f,
		 0.5f,  0.5f,  1.f, 0.f,
		 0.5f, -0.5f,  1.f, 1.f,
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

	lastTime = glfwGetTime();
	defaultUI = true;

	// Кнопки
	buttonsGame.push_back(std::make_shared<Button>(glm::vec2(-575, 300), glm::vec2(80, 80), TextureManager::get("Sawmill"), "Sawmill"));
	buttonsGame.push_back(std::make_shared<Button>(glm::vec2(-575, 220), glm::vec2(80, 80), TextureManager::get("Felled"), "Felled"));
	buttonsGame.push_back(std::make_shared<Button>(glm::vec2(-575, 140), glm::vec2(80, 80), TextureManager::get("Mine"), "Mine"));

	buttonsUI.push_back(std::make_shared<Button>(glm::vec2(-575, 300), glm::vec2(80, 80), TextureManager::get("Warehouse"), "Warehouse"));
}

void MapLayer::update()
{
	// Управление
	if (Keyboard::getKeyState(GLFW_KEY_W) && viewGame->getCenter().y > -1150)
		viewGame->move({ 0.f, speed });

	if (Keyboard::getKeyState(GLFW_KEY_S) && viewGame->getCenter().y < 75)
		viewGame->move({ 0.f, -speed });

	if (Keyboard::getKeyState(GLFW_KEY_A) && viewGame->getCenter().x < -175)
		viewGame->move({ -speed, 0.f });

	if (Keyboard::getKeyState(GLFW_KEY_D) && viewGame->getCenter().x > -1750)
		viewGame->move({ speed, 0.f });

	if (Keyboard::getKeyState(GLFW_KEY_Q) && viewGame->getScale() < 7.5)
		viewGame->setScale(viewGame->getScale() + 0.1f);

	if (Keyboard::getKeyState(GLFW_KEY_E) && viewGame->getScale() > .75)
		viewGame->setScale(viewGame->getScale() - 0.1f);

	// Переменные
	glm::vec2 mousePosition = Mouse::getCoordinates();
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
	if (defaultUI)
	{
		for (auto button : buttonsGame)
		{
			if (button->contains(cursorUI) && Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
				pickedBuilding = button;
		}
	}

	if (extensionUI)
	{
		for (auto button : buttonsUI)
		{
			if (button->contains(cursorUI) && Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
				pickedBuilding = button;
		}
	}

	// Выделение клетки
	if (Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		pickedBuilding = nullptr;

		if (transportingUI)
		{
			for (auto tile : allTiles)
			{
				if (tile->contains(cursorGame) && tile != selectedTile)
				{
					for (auto building : buildings)
					{
						if (building->getTile() == tile)
						{
							selectedBuilding->setTransportationTarget(building);
							break;
						}
					}
				}
			}
		}

		if (extensionUI)
		{
			for (auto tile : map->getNeighbors(selectedTile))
			{
				if (tile->contains(cursorGame))
				{
					if (selectedExtensionTile != tile || selectedExtensionTile == nullptr)
					{
						selectedExtensionTile = tile;

						for (auto building : buildings)
						{
							if (building->getTile() == selectedExtensionTile)
							{
								selectedExtensionBuilding = building;
								break;
							}
							else
								selectedExtensionBuilding = nullptr;
						}
					}
					else
					{
						selectedExtensionTile = nullptr;
						selectedExtensionBuilding = nullptr;
					}
					break;
				}
			}
		}

		if (defaultUI)
		{
			for (auto tile : allTiles)
			{
				if (tile->contains(cursorGame))
				{
					if (selectedTile != tile || selectedTile == nullptr)
					{
						selectedTile = tile;

						for (auto building : buildings)
						{
							if (building->getTile() == selectedTile)
							{
								selectedBuilding = building;
								break;
							}
							else
								selectedBuilding = nullptr;
						}
					}
					else
					{
						selectedTile = nullptr;
						selectedBuilding = nullptr;
					}
					break;
				}
			}
		}
	}

	// Постройка зданий
	if (pickedBuilding != nullptr && (selectedBuilding == nullptr || selectedExtensionBuilding == nullptr))
	{
		if (defaultUI)
            if (treasuryMoney - buildingCost(pickedBuilding->getBuildingType()) >= 0)
            {
                switch (pickedBuilding->getBuildingType())
                {
                    case BuildingType::Sawmill:
                        buildings.push_back(std::make_shared<Sawmill>(selectedTile));
						selectedBuilding = buildings.back();
                        treasuryMoney -= buildingCost(pickedBuilding->getBuildingType());
                        break;

                    case BuildingType::Felled:
						if (selectedTile->getTerrainType() == TerrainType::Forest)
						{
							buildings.push_back(std::make_shared<Felled>(selectedTile));
							selectedBuilding = buildings.back();
							treasuryMoney -= buildingCost(pickedBuilding->getBuildingType());
						}
                        break;

                    case BuildingType::Mine:
                        if (selectedTile->getTerrainType() == TerrainType::Mountain)
                        {
                            buildings.push_back(std::make_shared<Mine>(selectedTile));
							selectedBuilding = buildings.back();
                            treasuryMoney -= buildingCost(pickedBuilding->getBuildingType());
                        }
                        break;
                }
            }

		if (extensionUI)
		{
			switch (pickedBuilding->getBuildingType())
			{
				case BuildingType::Warehouse:
					if (selectedBuilding->getExtensionAmount(BuildingType::Warehouse) < 2)
					{
						buildings.push_back(std::make_shared<Warehouse>(selectedExtensionTile, selectedBuilding));
						selectedBuilding->setExtension(buildings.back());
						selectedExtensionBuilding = buildings.back();
					}
					break;
			}
		}

		pickedBuilding = nullptr;
	}

	// Снос здания
	if (Keyboard::isKeyPressed(GLFW_KEY_DELETE) && (selectedBuilding != nullptr || selectedExtensionBuilding != nullptr))
	{
		int i = 0;

		if (selectedExtensionBuilding != nullptr)
		{
			for (auto building : buildings)
			{
				if (building == selectedExtensionBuilding)
				{
					buildings.erase(buildings.begin() + i);
					break;
				}

				i++;
			}
		}
		else
		{
			for (auto building : buildings)
			{
				if (building == selectedBuilding)
				{
					for (auto extensionBuilding : building->getExtensionBuildings())
					{
						buildings.erase(buildings.begin() + i);
					}

					buildings.erase(buildings.begin() + i);
					break;
				}

				i++;
			}
		}

		// Удаление в виде цели для транспортировки
		for (auto building : buildings)
		{
			for (auto target : building->getTransportationTargets())
			{
				if (std::find(buildings.begin(), buildings.end(), target) == buildings.end())
					building->setTransportationTarget(target);
			}
		}

		// Удаление в виде пристройки
		for (auto building : buildings)
		{
			for (auto target : building->getExtensionBuildings())
			{
				if (std::find(buildings.begin(), buildings.end(), target) == buildings.end())
					building->setExtension(target);
			}
		}
	}

	// Выбор типа интерфейса
	if (selectedBuilding != nullptr)
	{
		if (Keyboard::isKeyPressed(GLFW_KEY_T))
		{
			if (transportingUI)
			{
				transportingUI = false;
			}
			else
			{
				transportingUI = true;
			}

			extensionUI = false;
			selectedExtensionBuilding = nullptr;
			selectedExtensionTile = nullptr;
		}

		if (Keyboard::isKeyPressed(GLFW_KEY_X))
		{
			if (extensionUI)
			{
				extensionUI = false;
			}
			else
			{
				extensionUI = true;
			}

			transportingUI = false;
			selectedExtensionBuilding = nullptr;
			selectedExtensionTile = nullptr;
		}
	}
	
	if (transportingUI || extensionUI)
		defaultUI = false;
	else
		defaultUI = true;

	for (auto tile : allTiles)
	{
		if (tile->contains(cursorGame))
			pointedTile = tile;
	}

	// Debug
	if (debug)
	{
		int number = 0;
		std::cout << std::endl;

		if (transportingUI) 
			std::cout << "UI Mode: Transporting" << std::endl;
		if (extensionUI) 
			std::cout << "UI Mode: Extension" << std::endl;
		if (defaultUI)
			std::cout << "UI Mode: Default" << std::endl;

		std::cout << "Treasury Money: " << round(treasuryMoney) << " coins" << std::endl;
		std::cout << "Upkeep: " << round(totalUpkeep * 3600) << " coins / minute" << std::endl;
		std::cout << "Map Storage:" << std::endl;
		for (int i = 0; i < 15; i++)
		{
			if (storageMap[(ResourseType)i] != 0) std::cout << "   " << getResourceName( (ResourseType)i ) << " - " << storageMap[(ResourseType)i] << std::endl;
		}
	}
}

void MapLayer::render()
{
	auto shader = ShaderManager::get("Texture");
	shader->bind();
	shader->setInt("ourTexture", 0);
	vao->bind();

	//// Карта
	shader->setMat4("view", viewGame->getMatrix());

	// Фон
	TextureManager::get("Paper")->bind();
	for (int x = -1; x < 6; x++)
	{
		for (int y = -1; y < 4; y++)
		{
			glm::mat4 transformation = glm::translate(glm::mat4(1), glm::vec3(x * 500, y * 500, 0));
			transformation = glm::scale(transformation, glm::vec3(500, 500, 0));

			shader->setMat4("transform", transformation);

			glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
		}
	}

	// Отрисовка клеток
	std::vector<std::shared_ptr<Tile>> allTiles = map->getTiles();
	for (auto tile : allTiles)
	{
		shader->setMat4("transform", tile->getTransform());

		// Клетка
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
		case TerrainType::Forest:
			TextureManager::get("Forest")->bind();
			break;
		}

		glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);

		// Обводка
		if (tile == pointedTile)
			TextureManager::get("Hex")->bind();
		else
			TextureManager::get("PointedHex")->bind();

		if (tile == selectedTile)
			TextureManager::get("SelectedHex")->bind();

		if (extensionUI && tile == selectedExtensionTile)
			TextureManager::get("SelectedTransportHex")->bind();

		glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
	}

	if (transportingUI)
	{
		TextureManager::get("SelectedTransportHex")->bind();

		for (auto building : selectedBuilding->getTransportationTargets())
		{
			shader->setMat4("transform", building->getTile()->getTransform());
			glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
		}
	}

	// Отрисовка зданий
	for (auto building : buildings)
	{
		shader->setMat4("transform", building->getTransform());
		building->getTexture()->bind();
		glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
	}

	//// Интерфейс
	shader->setMat4("view", viewUI->getMatrix());

	// Отрисовка кнопок
	if (defaultUI)
	{
		// Без выделенной клетки
		for (auto button : buttonsGame)
		{
			shader->setMat4("transform", button->getTransform());
			button->getTexture()->bind();
			glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
		}
	}

	if (extensionUI)
	{
		// При выделенной клетке
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