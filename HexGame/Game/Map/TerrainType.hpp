#pragma once

enum class TerrainType
{
	Flatland = 0,
	Hill,
	Mountain
};

bool isTerrainCrossable(TerrainType type);
