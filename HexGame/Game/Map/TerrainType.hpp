#pragma once

enum class TerrainType
{
	Flatland,
	Hill,
	Mountain
};

bool isTerrainCrossable(TerrainType type);
