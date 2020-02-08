#pragma once

enum class BuildingType
{
	Sawmill = 0,
	Felled,
	Mine,

	Warehouse
};

int buildingCost(BuildingType);