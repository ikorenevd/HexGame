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
	TextureManager::add("Frame", std::make_shared<Texture>("Assets\\Textures\\Frame.png", ColorModel::RGBA, TextureFilter::Linear));

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
	TextureManager::add("TradingWarehouse", std::make_shared<Texture>("Assets\\Textures\\Buildings\\TradingWarehouse.png", ColorModel::RGBA));
	TextureManager::add("WarehouseExtension", std::make_shared<Texture>("Assets\\Textures\\Buildings\\WarehouseExtension", ColorModel::RGBA));
	TextureManager::add("Warehouse", std::make_shared<Texture>("Assets\\Textures\\Buildings\\Warehouse.png", ColorModel::RGBA));

	TextureManager::add("Felled_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\Felled.png", ColorModel::RGBA));
	TextureManager::add("Sawmill_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\Sawmill.png", ColorModel::RGBA));
	TextureManager::add("FurnitureManufacture_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\FurnitureManufacture.png", ColorModel::RGBA));
	TextureManager::add("PlanksManufacture_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\PlanksManufacture.png", ColorModel::RGBA));
	TextureManager::add("Mine_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\Mine.png", ColorModel::RGBA));
	TextureManager::add("AdditionalMine_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\AdditionalMine.png", ColorModel::RGBA));
	TextureManager::add("Foundry_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\Foundry.png", ColorModel::RGBA));
	TextureManager::add("AdditionalOven_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\AdditionalOven.png", ColorModel::RGBA));
	TextureManager::add("RailBeamWorkshop_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\RailBeamWorkshop.png", ColorModel::RGBA));
	TextureManager::add("MachineShop_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\MachineShop.png", ColorModel::RGBA));
	TextureManager::add("MachineShopExtension_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\MachineShopExtension.png", ColorModel::RGBA));
	TextureManager::add("Armory_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\Armory.png", ColorModel::RGBA));
	TextureManager::add("ArmoryExtension_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\ArmoryExtension.png", ColorModel::RGBA));
	TextureManager::add("Farm_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\Farm.png", ColorModel::RGBA));
	TextureManager::add("Pasture_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\Pasture.png", ColorModel::RGBA));
	TextureManager::add("SheepPasture_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\SheepPasture.png", ColorModel::RGBA));
	TextureManager::add("Field_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\Field.png", ColorModel::RGBA));
	TextureManager::add("CottonField_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\CottonField.png", ColorModel::RGBA));
	TextureManager::add("TradingWarehouse_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\TradingWarehouse.png", ColorModel::RGBA));
	TextureManager::add("WarehouseExtension_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\WarehouseExtension", ColorModel::RGBA));
	TextureManager::add("Warehouse_Text", std::make_shared<Texture>("Assets\\Textures\\Icons\\Buildings\\Warehouse.png", ColorModel::RGBA));

	TextureManager::add("RawWood", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\RawWood.png", ColorModel::RGBA));
	TextureManager::add("ProcessedWood", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\ProcessedWood.png", ColorModel::RGBA));
	TextureManager::add("Plank", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\Plank.png", ColorModel::RGBA));
	TextureManager::add("Ore", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\Ore.png", ColorModel::RGBA));
	TextureManager::add("PreciousOre", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\PreciousOre.png", ColorModel::RGBA));
	TextureManager::add("Coal", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\Coal.png", ColorModel::RGBA));
	TextureManager::add("Stone", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\Stone.png", ColorModel::RGBA));
	TextureManager::add("Metal", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\Metal.png", ColorModel::RGBA));
	TextureManager::add("PreciousMetal", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\PreciousMetal.png", ColorModel::RGBA));
	TextureManager::add("Machine", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\Machine.png", ColorModel::RGBA));
	TextureManager::add("Rail", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\Rail.png", ColorModel::RGBA));
	TextureManager::add("Beam", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\Beam.png", ColorModel::RGBA));
	TextureManager::add("Weapon", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\Weapon.png", ColorModel::RGBA));
	TextureManager::add("Jewelry", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\Jewelry.png", ColorModel::RGBA));
	TextureManager::add("Cereal", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\Cereal.png", ColorModel::RGBA));
	TextureManager::add("Meat", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\Meat.png", ColorModel::RGBA));
	TextureManager::add("Cotton", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\Cotton.png", ColorModel::RGBA));
	TextureManager::add("Furniture", std::make_shared<Texture>("Assets\\Textures\\Icons\\Resources\\Furniture.png", ColorModel::RGBA));

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
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-485, 300), glm::vec2(250, 50), TextureManager::get("Felled_Text"), "Felled"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-485, 250), glm::vec2(250, 50), TextureManager::get("Sawmill_Text"), "Sawmill"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-485, 200), glm::vec2(250, 50), TextureManager::get("FurnitureManufacture_Text"), "FurnitureManufacture"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-485, 150), glm::vec2(250, 50), TextureManager::get("Mine_Text"), "Mine"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-485, 100), glm::vec2(250, 50), TextureManager::get("Foundry_Text"), "Foundry"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-485, 50), glm::vec2(250, 50), TextureManager::get("MachineShop_Text"), "MachineShop"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-485, 0), glm::vec2(250, 50), TextureManager::get("Armory_Text"), "Armory"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-485, -50), glm::vec2(250, 50), TextureManager::get("Farm_Text"), "Farm"));
	buttonsBuildings.push_back(std::make_shared<Button>(glm::vec2(-485, -100), glm::vec2(250, 50), TextureManager::get("TradingWarehouse_Text"), "TradingWarehouse"));

	buttonsExtensionBuildings.push_back(std::make_shared<Button>(glm::vec2(-485, 300), glm::vec2(250, 50), TextureManager::get("Warehouse_Text"), "Warehouse"));
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

	// Транспортировка, обновление состояние зданий, общей стоимости их содержания и казны города
	totalUpkeep = 0;

	for (auto building : buildings)
	{
		building->update();

		if (!building->isFrozen() and building->isFunctioning())
		{	
			totalUpkeep += building->getUpkeep();

			// Продажа ресурсов
			if (building->getBuildingType() == BuildingType::TradingWarehouse)
			{
				for (int i = 0; i < 20; i++)	
				{
					if (building->getStorage((ResourseType)i) >= 50)
					{
						treasuryMoney += getResourcePrice((ResourseType)i) * building->getStorage((ResourseType)i);
						building->setStorage((ResourseType)i, -building->getStorage((ResourseType)i));
					}
				};
			}

			// Транспортировка
			int transportationSpeed = 15;

			for (int i = 0; i < 20; i++)
			{
				if (building->getStorage((ResourseType)i) >= transportationSpeed)
				{
					float targets = 0;

					for (auto target : building->getTransportationTargets())
					{
						if (!target.first->isFrozen() && !target.first->isStorageFull() && target.first->getDefaultProduction(target.second) < 0 && target.second == (ResourseType)i)
						{
							targets++;
						}
					}

					for (auto target : building->getTransportationTargets())
					{
						if (!target.first->isFrozen() && !target.first->isStorageFull() && target.first->getDefaultProduction(target.second) < 0 && target.second == (ResourseType)i)
						{
							treasuryMoney -= building->getTile()->getDistance(target.first->getTile());

							building->setStorage(target.second, -transportationSpeed / targets);
							target.first->setStorage(target.second, transportationSpeed / targets);
						}
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
	storageMap = {};

	for (std::shared_ptr<Building> building : buildings)
	{
		for (int i = 0; i < 15; i++)
		{
			storageMap[(ResourseType)i] += building->getStorage((ResourseType)i);
		}
	}

	// Кнопки
	switch (interface)
	{
	case UI::Default:
		for (auto button : buttonsBuildings)
		{
			if (button->contains(cursorUI) && Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				pickedBuildingButton = button;
				break;
			}
		}
		break;

	case UI::Transportation:
		for (auto button : buttonsResources)
		{
			if (button->contains(cursorUI) && Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				pickedResourceButton = button;
				break;
			}
		}
		break;

	case UI::Extension:
		for (auto button : buttonsExtensionBuildings)
		{
			if (button->contains(cursorUI) && Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				pickedBuildingButton = button;
				break;
			}
		}
		break;
	}

	// Выделение клетки
	if (Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		pickedBuildingButton = nullptr;
		pickedResourceButton = nullptr;

		switch (interface)
		{
		case UI::Default:
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
			break;
		case UI::Transportation:
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
			break;
		case UI::Extension:
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
			break;
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
	if (interface == UI::Default && pickedBuildingButton != nullptr && selectedBuilding == nullptr && selectedTile != nullptr)
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

			case BuildingType::Mine:
				if (selectedTile->getTerrainType() == TerrainType::Mountain)
				{
					buildings.push_back(std::make_shared<Mine>(selectedTile));
					selectedBuilding = buildings.back();
					treasuryMoney -= getBuildingPrice(pickedBuildingButton->getBuildingType());
				}
				break;

			case BuildingType::TradingWarehouse:
				buildings.push_back(std::make_shared<TradingWarehouse>(selectedTile));
				selectedBuilding = buildings.back();
				treasuryMoney -= getBuildingPrice(pickedBuildingButton->getBuildingType());
				break;

			case BuildingType::Foundry:
				buildings.push_back(std::make_shared<Foundry>(selectedTile));
				selectedBuilding = buildings.back();
				treasuryMoney -= getBuildingPrice(pickedBuildingButton->getBuildingType());
				break;

			case BuildingType::Farm:
				buildings.push_back(std::make_shared<Farm>(selectedTile));
				selectedBuilding = buildings.back();
				treasuryMoney -= getBuildingPrice(pickedBuildingButton->getBuildingType());
				break;

			case BuildingType::MachineShop:
				buildings.push_back(std::make_shared<MachineShop>(selectedTile));
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

				buttonsResources = {};

				for (auto resource : selectedBuilding->getDefaultProductions())
				{
					if (resource.second > 0)
					{
						buttonsResources.push_back(std::make_shared<Button>(glm::vec2(-485, i), glm::vec2(250, 50), TextureManager::get(getResourceName(resource.first)), getResourceName(resource.first)));
						i = i - 50;
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

	// Наведение курсора
	pointedTile = nullptr;
	pointedButton = nullptr;

	for (auto tile : allTiles)
	{
		if (tile->contains(cursorGame))
			pointedTile = tile;
	}

	switch (interface)
	{
	case UI::Default:
		for (auto button : buttonsBuildings)
			if (button->contains(cursorUI))
				pointedButton = button;
		break;
	case UI::Transportation:
		for (auto button : buttonsResources)
			if (button->contains(cursorUI))
				pointedButton = button;
		break;
	case UI::Extension:
		for (auto button : buttonsExtensionBuildings)
			if (button->contains(cursorUI))
				pointedButton = button;
		break;
	}

	// Debug
	if (glfwGetTime() - lastTime >= 1)
	{
		std::cout << std::endl;

		switch (interface)
		{
		case UI::Default:
			std::cout << "UI Mode: Default" << std::endl;
			break;
		case UI::Transportation:
			std::cout << "UI Mode: Transporting" << std::endl;
			break;
		case UI::Extension:
			std::cout << "UI Mode: Extension" << std::endl;
			break;
		}

		std::cout << "Treasury Money: " << round(treasuryMoney) << " coins" << std::endl;
		std::cout << "Upkeep: " << round(totalUpkeep * 3600) << " coins / minute" << std::endl;
		std::cout << std::endl;

		for (auto building : buildings)
		{
			std::cout << "--- " << getBuildingName(building->getBuildingType()) << ": ";

			if (!(building->isFrozen()) && building->isFunctioning()) std::cout << "(Functioning) ";

			std::cout << std::endl;

			for (int i = 0; i < 20; i++)
			{
				if (building->getStorage((ResourseType)i) != 0) std::cout << "     " << getResourceName((ResourseType)i) << ": " << building->getStorage((ResourseType)i) << " | " << building->getProduction((ResourseType)i) << " / hour" << std::endl;
			}
		}

		lastTime++;
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

	if (pointedButton != nullptr)
	{
		shader->setMat4("transform", pointedButton->getTransform());
		TextureManager::get("Frame")->bind();
		glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
	}

	vao->unbind();
	shader->unbind();
}