#pragma once

enum class BuildingType
{
	Sawmill = 0,
	Felled,
	Mine
};

int buildingCost(BuildingType);