#pragma once

#include <Game/Map/TerrainType.hpp>

bool isTerrainCrossable(TerrainType type)
{
	switch (type)
	{
	case TerrainType::Flatland:
		return true;
		break;
	case TerrainType::Hill:
		return true;
		break;
	case TerrainType::Mountain:
		return false;
		break;
	case TerrainType::Forest:
		return true;
		break;
	}
}
