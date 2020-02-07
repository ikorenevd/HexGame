#pragma once

enum class TerrainType
{
	Flatland = 0,
	Hill,
	Mountain,
	Forest
};

bool isTerrainCrossable(TerrainType type);
