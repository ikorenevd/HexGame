#pragma once

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

int resourceSize(ResourseType);