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
	case ResourseType::Weapon:
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
	case ResourseType::Furniture:
		return 3;
		break;
	}
}

int getResourcePrice(ResourseType type)
{
	switch (type)
	{
	case ResourseType::RawWood:
		return 10;
		break;
	case ResourseType::ProcessedWood:
		return 5;
		break;
	case ResourseType::Plank:
		return 5;
		break;
	case ResourseType::Ore:
		return 15;
		break;
	case ResourseType::PreciousOre:
		return 25;
		break;
	case ResourseType::Coal:
		return 10;
		break;
	case ResourseType::Stone:
		return 10;
		break;
	case ResourseType::Metal:
		return 20;
		break;
	case ResourseType::PreciousMetal:
		return 40;
		break;
	case ResourseType::Machine:
		return 50;
		break;
	case ResourseType::Rail:
		return 75;
		break;
	case ResourseType::Beam:
		return 40;
		break;
	case ResourseType::Weapon:
		return 100;
		break;
	case ResourseType::Jewelry:
		return 75;
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
	case ResourseType::Furniture:
		return 25;
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
	case ResourseType::Weapon:
		return "Weapon";
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
	case ResourseType::Furniture:
		return "Furniture";
		break;
	}
}