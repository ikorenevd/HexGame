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
	TextureManager::add("Paper", std::make_shared<Texture>("Assets\\Textures\\Paper.png", ColorModel::RGBA, TextureFilter::Linear));
	TextureManager::add("Overlay", std::make_shared<Texture>("Assets\\Textures\\Overlay.png", ColorModel::RGBA, TextureFilter::Linear));

	TextureManager::add("Hex", std::make_shared<Texture>("Assets\\Textures\\Hex\\Hex.png", ColorModel::RGBA));
	TextureManager::add("PointedHex", std::make_shared<Texture>("Assets\\Textures\\Hex\\PointedHex.png", ColorModel::RGBA));
	TextureManager::add("SelectedHex", std::make_shared<Texture>("Assets\\Textures\\Hex\\SelectedHex.png", ColorModel::RGBA));
	TextureManager::add("ExtensionSelectedHex", std::make_shared<Texture>("Assets\\Textures\\Hex\\ExtensionSelectedHex.png", ColorModel::RGBA));
	TextureManager::add("TransportHex", std::make_shared<Texture>("Assets\\Textures\\Hex\\TransportHex.png", ColorModel::RGBA));

	TextureManager::add("Flatland", std::make_shared<Texture>("Assets\\Textures\\Landscape\\Flatland.png", ColorModel::RGBA));
	TextureManager::add("Hill", std::make_shared<Texture>("Assets\\Textures\\Landscape\\Hill.png", ColorModel::RGBA));
	TextureManager::add("Mountain", std::make_shared<Texture>("Assets\\Textures\\Landscape\\Mountain.png", ColorModel::RGBA));
	TextureManager::add("Forest", std::make_shared<Texture>("Assets\\Textures\\Landscape\\Forest.png", ColorModel::RGBA));

	TextureManager::add("Sawmill", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Sawmill.png", ColorModel::RGBA));
	TextureManager::add("Felled", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Felled.png", ColorModel::RGBA));
	TextureManager::add("Mine", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Mine.png", ColorModel::RGBA));
	TextureManager::add("Warehouse", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Warehouse.png", ColorModel::RGBA));

	TextureManager::add("RawWood", std::make_shared<Texture>("Assets\\Textures\\Resource\\RawWood.png", ColorModel::RGBA));

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
	interface = UI::Default;

	// Кнопки
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-575, 300), glm::vec2(60, 60), TextureManager::get("Sawmill"), "Sawmill"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-575, 240), glm::vec2(60, 60), TextureManager::get("Felled"), "Felled"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-575, 180), glm::vec2(60, 60), TextureManager::get("Mine"), "Mine"));

	buttonsExtensionBuildings.push_back(std::make_shared<Button>(glm::vec2(-575, 300), glm::vec2(80, 80), TextureManager::get("Warehouse"), "Warehouse"));

	buttonsResources.push_back(std::make_shared<Button>(glm::vec2(-575, 300), glm::vec2(80, 80), TextureManager::get("RawWood"), "RawWood"));
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

	// Обновление состояние зданий, общей стоимости их содержания и казны города
	totalUpkeep = 0;

	for (auto building : buildings)
	{
		building->update();

		if (!building->isFrozen() and building->isFunctioning())
		{
			totalUpkeep += building->getUpkeep();

			// Количество целей транспортировки
			int transportationTargetsAmount = 0;

			if (building->getTransportationTargets().size() > 0)
			{
				for (auto transportationTarget : building->getTransportationTargets())
				{
					if (!(transportationTarget.first->isStorageFull()) && (building->getResourseAmount(transportationTarget.second) > 0))
					{
						transportationTargetsAmount++;
					}
				}
			}

			// Транспортировка
			if (building->getTransportationTargets().size() > 0)
			{
				for (auto transportationTarget : building->getTransportationTargets())
				{
					if (!(transportationTarget.first->isStorageFull()) && (building->getResourseAmount(transportationTarget.second) > 0))
					{
						building->setStorage(transportationTarget.second, -building->getProduction(transportationTarget.second) / transportationTargetsAmount/  3600.);
						transportationTarget.first->setStorage(transportationTarget.second, +building->getProduction(transportationTarget.second) / transportationTargetsAmount/ 3600.);

						totalUpkeep += building->getTile()->getDistance(transportationTarget.first->getTile()) / 3600.;
					}
				}
			}
		}
		else
		{
			totalUpkeep += building->getUpkeep() / 5;
		}
	}

	treasuryMoney -= totalUpkeep;

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
	if (interface == UI::Default)
	{
		for (auto button : buttonsBuildings)
		{
			if (button->contains(cursorUI) && Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				pickedBuildingButton = button;
				break;
			}
		}
	}

	if (interface == UI::Extension)
	{
		for (auto button : buttonsExtensionBuildings)
		{
			if (button->contains(cursorUI) && Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				pickedBuildingButton = button;
				break;
			}
		}
	}

	if (interface == UI::Transportation)
	{
		for (auto button : buttonsResources)
		{
			if (button->contains(cursorUI) && Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				pickedResourceButton = button;
				break;
			}
		}
	}

	// Выделение клетки
	if (Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		pickedBuildingButton = nullptr;
		pickedResourceButton = nullptr;

		if (interface == UI::Default)
		{
			for (auto tile : allTiles)
			{
				if (tile->contains(cursorGame))
				{
					if (selectedTile != tile || selectedTile == nullptr)
					{
						selectedTile = tile;
						break;
					}
					else
					{
						selectedTile = nullptr;
					}
				}
			}
		}

		if (interface == UI::Extension)
		{
			for (auto tile : map->getNeighbors(selectedTile))
			{
				if (tile->contains(cursorGame))
				{
					if (selectedExtensionTile != tile || selectedExtensionTile == nullptr)
					{
						selectedExtensionTile = tile;
						break;
					}
					else
					{
						selectedExtensionTile = nullptr;
					}
				}
			}
		}

		if (interface == UI::Transportation)
		{
			for (auto building : buildings)
			{
				if (building->getTile()->contains(cursorGame) && building != selectedBuilding && building->getParent() == nullptr)
				{
					if (selectedTransportationTile != building->getTile() || selectedTransportationTile == nullptr)
					{
						selectedTransportationTile = building->getTile();
						break;
					}
					else
					{
						selectedTransportationTile = nullptr;
					}
				}
			}
		}

		// Выделение здания
		selectedBuilding = nullptr;
		selectedExtensionBuilding = nullptr;
		selectedTransportationBuilding = nullptr;

		if (selectedTile != nullptr)
			for (auto building : buildings)
			{
				if (building->getTile() == selectedTile && building->getParent() == nullptr)
				{
					selectedBuilding = building;
					break;
				}
				else
				{
					selectedBuilding = nullptr;
				}
					
				if (building->getTile() == selectedTile && building->getParent() != nullptr)
				{
					selectedExtensionBuilding = building;
					break;
				}
				else
				{
					selectedExtensionBuilding = nullptr;
				}
			}

		if (selectedExtensionTile != nullptr)
			for (auto building : buildings)
			{
				if (building->getTile() == selectedExtensionTile && building->getParent() != nullptr)
				{
					selectedExtensionBuilding = building;
					break;
				}
				else
				{
					selectedExtensionBuilding = nullptr;
				}
			}

		if (selectedTransportationTile != nullptr)
		{
			for (auto building : buildings)
			{
				if (building->getTile() == selectedTransportationTile)
				{
					selectedTransportationBuilding = building;
					break;
				}
				else
				{
					selectedTransportationBuilding = nullptr;
				}

			}
		}
	}

	// Постройка зданий
	if (interface == UI::Default && pickedBuildingButton != nullptr && selectedBuilding == nullptr && (selectedTile != nullptr || selectedExtensionTile != nullptr))
	{
		if (treasuryMoney - buildingCost(pickedBuildingButton->getBuildingType()) >= 0)
		{
			switch (pickedBuildingButton->getBuildingType())
			{
			case BuildingType::Sawmill:
				buildings.push_back(std::make_shared<Sawmill>(selectedTile));
				selectedBuilding = buildings.back();
				treasuryMoney -= buildingCost(pickedBuildingButton->getBuildingType());
				break;

			case BuildingType::Felled:
				if (selectedTile->getTerrainType() == TerrainType::Forest)
				{
					buildings.push_back(std::make_shared<Felled>(selectedTile));
					selectedBuilding = buildings.back();
					treasuryMoney -= buildingCost(pickedBuildingButton->getBuildingType());
				}
				break;

			case BuildingType::Mine:
				if (selectedTile->getTerrainType() == TerrainType::Mountain)
				{
					buildings.push_back(std::make_shared<Mine>(selectedTile));
					selectedBuilding = buildings.back();
					treasuryMoney -= buildingCost(pickedBuildingButton->getBuildingType());
				}
				break;
			}
		}
	}

	if (interface == UI::Extension && pickedBuildingButton != nullptr && selectedExtensionBuilding == nullptr && selectedExtensionTile != nullptr)
	{
		if (treasuryMoney - buildingCost(pickedBuildingButton->getBuildingType()) >= 0)
		{
			switch (pickedBuildingButton->getBuildingType())
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
	}

	if (selectedBuilding != nullptr || selectedExtensionBuilding != nullptr)
		pickedBuildingButton = nullptr;

	// Выбор клетки и ресурса для транспортировки
	if (selectedTransportationBuilding != nullptr && pickedResourceButton != nullptr)
	{
		selectedBuilding->setTransportationTarget(selectedTransportationBuilding, pickedResourceButton->getResourceType());
		pickedResourceButton = nullptr;
	}

	// Отмена транспортировки в здание
	if (Keyboard::isKeyPressed(GLFW_KEY_DELETE))
	{
		if (interface == UI::Transportation)
		{
			if (selectedTransportationBuilding != nullptr)
			{
				selectedBuilding->deleteTransportationTarget(selectedTransportationBuilding);
			}
		}
	}


	// Выбор типа интерфейса
	if (Keyboard::isKeyPressed(GLFW_KEY_ESCAPE))
	{
		interface = UI::Default;
	}

	if (selectedBuilding != nullptr)
	{
		if (Keyboard::isKeyPressed(GLFW_KEY_T))
		{
			if (interface != UI::Transportation)
			{
				interface = UI::Transportation;
			}
			else
			{
				interface = UI::Default;

				selectedTransportationTile = nullptr;
				selectedTransportationBuilding = nullptr;
			}
		}

		if (Keyboard::isKeyPressed(GLFW_KEY_X))
		{
			if (interface != UI::Extension)
			{
				interface = UI::Extension;
			}
			else
			{
				interface = UI::Default;

				selectedExtensionTile = nullptr;
				selectedExtensionBuilding = nullptr;
			}
		}
	}

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

		if (selectedBuilding != nullptr)
			std::cout << "Selected Building:" << selectedBuilding->getTile()->getCoordinates().x << selectedBuilding->getTile()->getCoordinates().y << selectedBuilding->getTile()->getCoordinates().z << std::endl;
		if (selectedTransportationBuilding != nullptr)
			std::cout << "Selected Transportation Building:" << selectedTransportationBuilding->getTile()->getCoordinates().x << selectedTransportationBuilding->getTile()->getCoordinates().y << selectedTransportationBuilding->getTile()->getCoordinates().z << std::endl;
		if (selectedTransportationTile != nullptr)
			std::cout << "Selected Transportation Tile:" << selectedTransportationTile->getCoordinates().x << selectedTransportationTile->getCoordinates().y << selectedTransportationTile->getCoordinates().z << std::endl;
		if (selectedTile != nullptr)
			std::cout << "Selected Tile:" << selectedTile->getCoordinates().x << selectedTile->getCoordinates().y << selectedTile->getCoordinates().z << std::endl;
		if (selectedExtensionBuilding != nullptr)
			std::cout << "Selected Ext Building:" << selectedExtensionBuilding->getTile()->getCoordinates().x << selectedExtensionBuilding->getTile()->getCoordinates().y << selectedExtensionBuilding->getTile()->getCoordinates().z << std::endl;
		if (selectedExtensionTile != nullptr)
			std::cout << "Selected Ext Tile:" << selectedExtensionTile->getCoordinates().x << selectedExtensionTile->getCoordinates().y << selectedExtensionTile->getCoordinates().z << std::endl;

		if (interface == UI::Transportation) 
			std::cout << "UI Mode: Transporting" << std::endl;
		if (interface == UI::Extension)
			std::cout << "UI Mode: Extension" << std::endl;
		if (interface == UI::Default)
			std::cout << "UI Mode: Default" << std::endl;

		std::cout << "Treasury Money: " << round(treasuryMoney) << " coins" << std::endl;
		std::cout << "Upkeep: " << round(totalUpkeep * 3600) << " coins / minute" << std::endl;
		std::cout << "Map Storage:" << std::endl;

		for (int i = 0; i < 15; i++)
		{
			if (storageMap[(ResourseType)i] != 0) std::cout << getResourceName( (ResourseType)i ) << " - " << storageMap[(ResourseType)i] << std::endl;
		}

		std::cout << std::endl;

		for (auto building : buildings)
		{
			std::cout << "Building " << number << ": ";

			for (int i = 0; i < 15; i++)
			{
				if (building->getResourseAmount((ResourseType)i) != 0) std::cout << "   " << getResourceName((ResourseType)i) << " - " << building->getResourseAmount((ResourseType)i);
			}

			number++;

			std::cout << std::endl;
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

		if (interface == UI::Extension && tile == selectedExtensionTile)
			TextureManager::get("ExtensionSelectedHex")->bind();

		if (interface == UI::Transportation)
			if (selectedTransportationTile == tile)
				TextureManager::get("ExtensionSelectedHex")->bind();

		glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
	}

	if (interface == UI::Transportation)
	{
		TextureManager::get("TransportHex")->bind();

		for (auto building : selectedBuilding->getTransportationTargets())
		{
			shader->setMat4("transform", building.first->getTile()->getTransform());
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

	// Overlay
	glm::mat4 transformation = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
	transformation = glm::scale(transformation, glm::vec3(viewGame->getSize().x, viewGame->getSize().y, 0));

	shader->setMat4("transform", transformation);
	TextureManager::get("Overlay")->bind();

	glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);

	// Отрисовка кнопок
	if (interface == UI::Default)
	{
		// Без выделенной клетки
		for (auto button : buttonsBuildings)
		{
			shader->setMat4("transform", button->getTransform());
			button->getTexture()->bind();
			glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
		}
	}

	if (interface == UI::Extension)
	{
		// При выделенной клетке
		for (auto button : buttonsExtensionBuildings)
		{
			shader->setMat4("transform", button->getTransform());
			button->getTexture()->bind();
			glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
		}
	}

	if (interface == UI::Transportation)
	{
		for (auto button : buttonsResources)
		{
			shader->setMat4("transform", button->getTransform());
			button->getTexture()->bind();
			glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
		}
	}

	vao->unbind();
	shader->unbind();
}