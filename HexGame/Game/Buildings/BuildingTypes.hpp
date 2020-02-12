#pragma once

enum class BuildingType
{
	Felled,
	Sawmill,
	FurnitureManufacture,
		PlanksManufacture,
	Mine,
		AdditionalMine,
	Foundry,
		AdditionalOven,
		RailBeamWorkshop,
	MachineShop,
		MachineShopExtension,
	Armory,
		ArmoryExtension,
	Farm,
		Pasture,
		SheepPasture,
		Field,
		CottonField,
	TradingWarehouse,
		WarehouseExtension,
	Warehouse
};

int getBuildingPrice(BuildingType);