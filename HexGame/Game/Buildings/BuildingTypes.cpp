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