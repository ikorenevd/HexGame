// TO DO: мясо, шерсть, хлопок, пшено

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

int resourceSize(ResourseType type)
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