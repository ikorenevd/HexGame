#pragma once
#include <string>

enum class ResourseType
{
	RawWood = 0,
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
	Wearpon,
	Jewelry
};

int getResourceSize(ResourseType);
std::string getResourceName(ResourseType);