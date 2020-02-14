#pragma once
#include <string>

enum class ResourseType
{
	RawWood,
	ProcessedWood,
	Plank,
	Ore,
	PreciousOre,
	Coal,
	Stone,
	Metal,
	PreciousMetal,
	Machine,
	Rail,
	Beam,
	Weapon,
	Jewelry,
	Cereal,
	Meat,
	Cotton,
	Furniture
};

int getResourceSize(ResourseType);
int getResourcePrice(ResourseType);
std::string getResourceName(ResourseType);