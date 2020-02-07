#include <Game/Buildings/ResourceTypes.hpp>

int getResourceSize(ResourseType type)
{
	switch (type)
	{
	case ResourseType::RawWood: return 5;
		break;

	case ResourseType::ProcessedWood: return 3;
		break;

	case ResourseType::Plank: return 1;
		break;

	case ResourseType::Ore: return 4;
		break;

	case ResourseType::PreciousOre: return 4;
		break;

	case ResourseType::Coal: return 2;
		break;

	case ResourseType::Stone: return 4;
		break;

	case ResourseType::Machine: return 10;
		break;

	case ResourseType::Rail: return 5;
		break;

	case ResourseType::Beam: return 5;
		break;

	case ResourseType::Wearpon: return 2;
		break;

	case ResourseType::Jewelry: return 1;
		break;
	}
}

std::string getResourceName(ResourseType type)
{
	switch (type)
	{
	case ResourseType::RawWood: return "RawWood";
		break;

	case ResourseType::ProcessedWood: return "ProcessedWood";
		break;

	case ResourseType::Plank: return "Plank";
		break;

	case ResourseType::Ore: return "Ore";
		break;

	case ResourseType::PreciousOre: return "PreciousOre";
		break;

	case ResourseType::Coal: return "Coal";
		break;

	case ResourseType::Stone: return "Stone";
		break;

	case ResourseType::Machine: return "Machine";
		break;

	case ResourseType::Rail: return "Rail";
		break;

	case ResourseType::Beam: return "Beam";
		break;

	case ResourseType::Wearpon: return "Wearpon";
		break;

	case ResourseType::Jewelry: return "Jewelry";
		break;
	}
}