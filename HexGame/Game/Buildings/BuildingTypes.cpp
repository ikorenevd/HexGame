#include <Game/Buildings/BuildingTypes.hpp>

int getBuildingPrice(BuildingType type)
{
	switch (type)
	{
    case BuildingType::Felled:
        return 125;
        break;
    case BuildingType::Sawmill:
        return 250;
        break;
    case BuildingType::FurnitureManufacture:
        return 250;
        break;
    case BuildingType::PlanksManufacture:
        return 100;
        break;
    case BuildingType::Mine:
        return 375;
        break;
    case BuildingType::AdditionalMine:
        return 150;
        break;
    case BuildingType::Foundry:
        return 750;
        break;
    case BuildingType::AdditionalOven:
        return 300;
        break;
    case BuildingType::RailBeamWorkshop:
        return 250;
        break;
    case BuildingType::MachineShop:
        return 500;
        break;
    case BuildingType::MachineShopExtension:
        return 200;
        break;
    case BuildingType::Armory:
        return 500;
        break;
    case BuildingType::ArmoryExtension:
        return 200;
        break;
    case BuildingType::Farm:
        return 250;
        break;
    case BuildingType::Pasture:
        return 200;
        break;
    case BuildingType::SheepPasture:
        return 200;
        break;
    case BuildingType::Field:
        return 100;
        break;
    case BuildingType::CottonField:
        return 200;
        break;
    case BuildingType::TradingWarehouse:
        return 250;
        break;
    case BuildingType::WarehouseExtension:
        return 100;
        break;
    case BuildingType::Warehouse:
        return 150;
        break;
    default:
        return 0;
        break;
	}
}

std::string getBuildingName(BuildingType type)
{
    switch (type)
    {
    case BuildingType::Felled:
        return "Felled";
        break;
    case BuildingType::Sawmill:
        return "Sawmill";
        break;
    case BuildingType::FurnitureManufacture:
        return "FurnitureManufacture";
        break;
    case BuildingType::PlanksManufacture:
        return "PlanksManufacture";
        break;
    case BuildingType::Mine:
        return "Mine";
        break;
    case BuildingType::AdditionalMine:
        return "AdditionalMine";
        break;
    case BuildingType::Foundry:
        return "Foundry";
        break;
    case BuildingType::AdditionalOven:
        return "AdditionalOven";
        break;
    case BuildingType::RailBeamWorkshop:
        return "RailBeamWorkshop";
        break;
    case BuildingType::MachineShop:
        return "MachineShop";
        break;
    case BuildingType::MachineShopExtension:
        return "MachineShopExtension";
        break;
    case BuildingType::Armory:
        return "Armory";
        break;
    case BuildingType::ArmoryExtension:
        return "ArmoryExtension";
        break;
    case BuildingType::Farm:
        return "Farm";
        break;
    case BuildingType::Pasture:
        return "Pasture";
        break;
    case BuildingType::SheepPasture:
        return "SheepPasture";
        break;
    case BuildingType::Field:
        return "Field";
        break;
    case BuildingType::CottonField:
        return "CottonField";
        break;
    case BuildingType::TradingWarehouse:
        return "TradingWarehouse";
        break;
    case BuildingType::WarehouseExtension:
        return "WarehouseExtension";
        break;
    case BuildingType::Warehouse:
        return "Warehouse";
        break;
    }
}