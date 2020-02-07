#include <Game/Buildings/BuildingTypes.hpp>

int buildingCost(BuildingType type)
{
	switch (type)
	{
	case BuildingType::Sawmill: return 150;
		break;

	case BuildingType::Felled: return 200;
		break;

	case BuildingType::Mine: return 250;
		break;
	}
}