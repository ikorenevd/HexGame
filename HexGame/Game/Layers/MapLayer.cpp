﻿#include <Game/Layers/MapLayer.hpp>

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

	TextureManager::add("Felled", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Felled.png", ColorModel::RGBA));
	TextureManager::add("Sawmill", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Sawmill.png", ColorModel::RGBA));
	TextureManager::add("FurnitureManufacture", std::make_shared<Texture>("Assets\\Textures\\Buildings\\FurnitureManufacture.png", ColorModel::RGBA));
	TextureManager::add("PlanksManufacture", std::make_shared<Texture>("Assets\\Textures\\Buildings\\PlanksManufacture.png", ColorModel::RGBA));
	TextureManager::add("Mine", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Mine.png", ColorModel::RGBA));
	TextureManager::add("AdditionalMine", std::make_shared<Texture>("Assets\\Textures\\Buildings\\AdditionalMine.png", ColorModel::RGBA));
	TextureManager::add("Foundry", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Foundry.png", ColorModel::RGBA));
	TextureManager::add("AdditionalOven", std::make_shared<Texture>("Assets\\Textures\\Buildings\\AdditionalOven.png", ColorModel::RGBA));
	TextureManager::add("RailBeamWorkshop", std::make_shared<Texture>("Assets\\Textures\\Buildings\\RailBeamWorkshop.png", ColorModel::RGBA));
	TextureManager::add("MachineShop", std::make_shared<Texture>("Assets\\Textures\\Buildings\\MachineShop.png", ColorModel::RGBA));
	TextureManager::add("MachineShopExtension", std::make_shared<Texture>("Assets\\Textures\\Buildings\\MachineShopExtension.png", ColorModel::RGBA));
	TextureManager::add("Armory", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Armory.png", ColorModel::RGBA));
	TextureManager::add("ArmoryExtension", std::make_shared<Texture>("Assets\\Textures\\Buildings\\ArmoryExtension.png", ColorModel::RGBA));
	TextureManager::add("Farm", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Farm.png", ColorModel::RGBA));
	TextureManager::add("Pasture", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Pasture.png", ColorModel::RGBA));
	TextureManager::add("SheepPasture", std::make_shared<Texture>("Assets\\Textures\\Buildings\\SheepPasture.png", ColorModel::RGBA));
	TextureManager::add("Field", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Field.png", ColorModel::RGBA));
	TextureManager::add("CottonField", std::make_shared<Texture>("Assets\\Textures\\Buildings\\CottonField.png", ColorModel::RGBA));
	TextureManager::add("CottonField", std::make_shared<Texture>("Assets\\Textures\\Buildings\\CottonField.png", ColorModel::RGBA));
	TextureManager::add("TradingWarehouse", std::make_shared<Texture>("Assets\\Textures\\Buildings\\TradingWarehouse.png", ColorModel::RGBA));
	TextureManager::add("WarehouseExtension", std::make_shared<Texture>("Assets\\Textures\\Buildings\\WarehouseExtension", ColorModel::RGBA));
	TextureManager::add("Warehouse", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Warehouse.png", ColorModel::RGBA));

	TextureManager::add("RawWood", std::make_shared<Texture>("Assets\\Textures\\Resource\\RawWood.png", ColorModel::RGBA));
	TextureManager::add("ProcessedWood", std::make_shared<Texture>("Assets\\Textures\\Resource\\ProcessedWood.png", ColorModel::RGBA));
	TextureManager::add("Plank", std::make_shared<Texture>("Assets\\Textures\\Resource\\Plank.png", ColorModel::RGBA));
	TextureManager::add("Ore", std::make_shared<Texture>("Assets\\Textures\\Resource\\Ore.png", ColorModel::RGBA));
	TextureManager::add("PreciousOre", std::make_shared<Texture>("Assets\\Textures\\Resource\\PreciousOre.png", ColorModel::RGBA));
	TextureManager::add("Coal", std::make_shared<Texture>("Assets\\Textures\\Resource\\Coal.png", ColorModel::RGBA));
	TextureManager::add("Stone", std::make_shared<Texture>("Assets\\Textures\\Resource\\Stone.png", ColorModel::RGBA));
	TextureManager::add("Metal", std::make_shared<Texture>("Assets\\Textures\\Resource\\Metal.png", ColorModel::RGBA));
	TextureManager::add("PreciousMetal", std::make_shared<Texture>("Assets\\Textures\\Resource\\PreciousMetal.png", ColorModel::RGBA));
	TextureManager::add("Machine", std::make_shared<Texture>("Assets\\Textures\\Resource\\Machine.png", ColorModel::RGBA));
	TextureManager::add("Rail", std::make_shared<Texture>("Assets\\Textures\\Resource\\Rail.png", ColorModel::RGBA));
	TextureManager::add("Beam", std::make_shared<Texture>("Assets\\Textures\\Resource\\Beam.png", ColorModel::RGBA));
	TextureManager::add("Wearpon", std::make_shared<Texture>("Assets\\Textures\\Resource\\Wearpon.png", ColorModel::RGBA));
	TextureManager::add("Jewelry", std::make_shared<Texture>("Assets\\Textures\\Resource\\Jewelry.png", ColorModel::RGBA));
	TextureManager::add("Cereal", std::make_shared<Texture>("Assets\\Textures\\Resource\\Cereal.png", ColorModel::RGBA));
	TextureManager::add("Meat", std::make_shared<Texture>("Assets\\Textures\\Resource\\Meat.png", ColorModel::RGBA));
	TextureManager::add("Cotton", std::make_shared<Texture>("Assets\\Textures\\Resource\\Cotton.png", ColorModel::RGBA));

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

	treasuryMoney = 10000;

	ShaderManager::add("Texture", std::make_shared<Shader>("Assets\\Shaders\\TextureVert.glsl", "Assets\\Shaders\\TextureFrag.glsl"));

	lastTime = glfwGetTime();
	interface = UI::Default;

	// Кнопки
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-575, 300), glm::vec2(60, 60), TextureManager::get("Felled"), "Felled"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-575, 240), glm::vec2(60, 60), TextureManager::get("Sawmill"), "Sawmill"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-575, 180), glm::vec2(60, 60), TextureManager::get("FurnitureManufacture"), "FurnitureManufacture"));
	/*buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-575, 120), glm::vec2(60, 60), TextureManager::get("Mine"), "Mine"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-575, 60), glm::vec2(60, 60), TextureManager::get("Foundry"), "Foundry"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-575, 0), glm::vec2(60, 60), TextureManager::get("MachineShop"), "MachineShop"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-575, -60), glm::vec2(60, 60), TextureManager::get("Armory"), "Armory"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-575, -120), glm::vec2(60, 60), TextureManager::get("Farm"), "Farm"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-575, -180), glm::vec2(60, 60), TextureManager::get("TradingWarehouse"), "TradingWarehouse"));*/

	buttonsExtensionBuildings.push_back(std::make_shared<Button>(glm::vec2(-575, 300), glm::vec2(80, 80), TextureManager::get("Warehouse"), "Warehouse"));
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
					if (!(transportationTarget.first->isStorageFull()) && (building->getStorage(transportationTarget.second) > 0))
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
					if (!(transportationTarget.first->isStorageFull()) && (building->getStorage(transportationTarget.second) > 0))
					{
						building->setStorage(transportationTarget.second, -building->getProduction(transportationTarget.second) / transportationTargetsAmount / 3600.);
						transportationTarget.first->setStorage(transportationTarget.second, +building->getProduction(transportationTarget.second) / transportationTargetsAmount / 3600.);

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
				storageMap[(ResourseType)i] += building->getStorage((ResourseType)i);
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
		if (treasuryMoney - getBuildingPrice(pickedBuildingButton->getBuildingType()) >= 0)
		{
			switch (pickedBuildingButton->getBuildingType())
			{
			case BuildingType::Felled:
				if (selectedTile->getTerrainType() == TerrainType::Forest)
				{
					buildings.push_back(std::make_shared<Felled>(selectedTile));
					selectedBuilding = buildings.back();
					treasuryMoney -= getBuildingPrice(pickedBuildingButton->getBuildingType());
				}
				break;

			case BuildingType::Sawmill:
				buildings.push_back(std::make_shared<Sawmill>(selectedTile));
				selectedBuilding = buildings.back();
				treasuryMoney -= getBuildingPrice(pickedBuildingButton->getBuildingType());
				break;

			case BuildingType::FurnitureManufacture:
				buildings.push_back(std::make_shared<FurnitureManufacture>(selectedTile));
				selectedBuilding = buildings.back();
				treasuryMoney -= getBuildingPrice(pickedBuildingButton->getBuildingType());
				break;
			}
		}
	}

	if (interface == UI::Extension && pickedBuildingButton != nullptr && selectedExtensionBuilding == nullptr && selectedExtensionTile != nullptr)
	{
		if (treasuryMoney - getBuildingPrice(pickedBuildingButton->getBuildingType()) >= 0)
		{
			switch (pickedBuildingButton->getBuildingType())
			{
			case BuildingType::Warehouse:
				buildings.push_back(std::make_shared<Warehouse>(selectedExtensionTile, selectedBuilding));
				selectedBuilding->setExtension(buildings.back());
				selectedExtensionBuilding = buildings.back();
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

	// Заморозка здания
	if (Keyboard::isKeyPressed(GLFW_KEY_F) && selectedBuilding != nullptr)
	{
		if (!selectedBuilding->isFrozen())
			selectedBuilding->setFrozen(true);
		else
			selectedBuilding->setFrozen(false);
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

				int i = 300;
				for (auto resource : selectedBuilding->getProductions())
				{
					if (resource.second > 0)
					{
						buttonsResources.push_back(std::make_shared<Button>(glm::vec2(-575, i), glm::vec2(80, 80), TextureManager::get(getResourceName(resource.first)), getResourceName(resource.first)));
						i = i - 60;
					}
				}
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
		std::cout << std::endl;

		if (interface == UI::Transportation) 
			std::cout << "UI Mode: Transporting" << std::endl;
		if (interface == UI::Extension)
			std::cout << "UI Mode: Extension" << std::endl;
		if (interface == UI::Default)
			std::cout << "UI Mode: Default" << std::endl;

		std::cout << "Treasury Money: " << round(treasuryMoney) << " coins" << std::endl;
		std::cout << "Upkeep: " << round(totalUpkeep * 3600) << " coins / minute" << std::endl;
		std::cout << std::endl;

		for (auto building : buildings)
		{
			std::cout << "--- " << getBuildingName(building->getBuildingType()) << ": ";

			if (!(building->isFrozen()) && building->isFunctioning()) std::cout << "(Functioning) ";

			std::cout << std::endl;

			for (int i = 0; i < 15; i++)
			{
				if (building->getStorage((ResourseType)i) != 0) std::cout << "     " << getResourceName((ResourseType)i) << " - " << building->getStorage((ResourseType)i) << " | " << building->getProduction((ResourseType)i) << " / hour" << std::endl;
			}
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