#include <Game/Buildings/ResourceTypes.hpp>

int getResourceSize(ResourseType type)
{
	switch (type)
	{
	case ResourseType::RawWood:
		return 10;
		break;
	case ResourseType::ProcessedWood:
		return 4;
		break;
	case ResourseType::Plank:
		return 1;
		break;
	case ResourseType::Ore:
		return 8;
		break;
	case ResourseType::PreciousOre:
		return 8;
		break;
	case ResourseType::Coal:
		return 8;
		break;
	case ResourseType::Stone:
		return 2;
		break;
	case ResourseType::Metal:
		return 2;
		break;
	case ResourseType::PreciousMetal:
		return 2;
		break;
	case ResourseType::Machine:
		return 4;
		break;
	case ResourseType::Rail:
		return 10;
		break;
	case ResourseType::Beam:
		return 10;
		break;
	case ResourseType::Wearpon:
		return 3;
		break;
	case ResourseType::Jewelry:
		return 1;
		break;
	case ResourseType::Cereal:
		return 1;
		break;
	case ResourseType::Meat:
		return 1;
		break;
	case ResourseType::Cotton:
		return 1;
		break;
	default:
		break;
	}
}

int getResourcePrice(ResourseType type)
{
	switch (type)
	{
	case ResourseType::RawWood:
		return 5;
		break;
	case ResourseType::ProcessedWood:
		return 5;
		break;
	case ResourseType::Plank:
		return 5;
		break;
	case ResourseType::Ore:
		return 5;
		break;
	case ResourseType::PreciousOre:
		return 5;
		break;
	case ResourseType::Coal:
		return 5;
		break;
	case ResourseType::Stone:
		return 5;
		break;
	case ResourseType::Metal:
		return 5;
		break;
	case ResourseType::PreciousMetal:
		return 5;
		break;
	case ResourseType::Machine:
		return 5;
		break;
	case ResourseType::Rail:
		return 5;
		break;
	case ResourseType::Beam:
		return 5;
		break;
	case ResourseType::Wearpon:
		return 5;
		break;
	case ResourseType::Jewelry:
		return 5;
		break;
	case ResourseType::Cereal:
		return 5;
		break;
	case ResourseType::Meat:
		return 5;
		break;
	case ResourseType::Cotton:
		return 5;
		break;
	default:
		break;
	}
}

std::string getResourceName(ResourseType type)
{
	switch (type)
	{
	case ResourseType::RawWood:
		return "RawWood";
		break;
	case ResourseType::ProcessedWood:
		return "ProcessedWood";
		break;
	case ResourseType::Plank:
		return "Plank";
		break;
	case ResourseType::Ore:
		return "Ore";
		break;
	case ResourseType::PreciousOre:
		return "PreciousOre";
		break;
	case ResourseType::Coal:
		return "Coal";
		break;
	case ResourseType::Stone:
		return "Stone";
		break;
	case ResourseType::Metal:
		return "Metal";
		break;
	case ResourseType::PreciousMetal:
		return "PreciousMetal";
		break;
	case ResourseType::Machine:
		return "Machine";
		break;
	case ResourseType::Rail:
		return "Rail";
		break;
	case ResourseType::Beam:
		return "Beam";
		break;
	case ResourseType::Wearpon:
		return "Wearpon";
		break;
	case ResourseType::Jewelry:
		return "Jewelry";
		break;
	case ResourseType::Cereal:
		return "Cereal";
		break;
	case ResourseType::Meat:
		return "Meat";
		break;
	case ResourseType::Cotton:
		return "Cotton";
		break;
	}
}