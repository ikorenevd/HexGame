#include <Game/Layers/ButtonsLayer.hpp>

Button::Button(const glm::vec2& pos, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, const std::string& name) :
	Transformable(pos, scale),
	texture(texture),
	name(name)
{
}

const std::shared_ptr<Texture>& Button::getTexture() const
{
	return texture;
}

bool Button::contains(const glm::vec2& point) const
{
	auto pos = getPosition();
	auto size = getScale();

	if ((pos.x + size.x / 2) >= point.x &&
		(pos.x - size.x / 2) <= point.x &&
		(pos.y + size.y / 2) >= point.y &&
		(pos.y - size.y / 2) <= point.y)
	{
		return true;
	};

	return false;
}

BuildingType Button::getBuildingType()
{
	if (name == "Felled") return BuildingType::Felled;
	if (name == "Sawmill") return BuildingType::Sawmill;
	if (name == "FurnitureManufacture") return BuildingType::FurnitureManufacture;
	if (name == "PlanksManufacture") return BuildingType::PlanksManufacture;
	if (name == "Mine") return BuildingType::Mine;
	if (name == "AdditionalMine") return BuildingType::AdditionalMine;
	if (name == "Foundry") return BuildingType::Foundry;
	if (name == "AdditionalOven") return BuildingType::AdditionalOven;
	if (name == "RailBeamWorkshop") return BuildingType::RailBeamWorkshop;
	if (name == "MachineShop") return BuildingType::MachineShop;
	if (name == "MachineShopExtension") return BuildingType::MachineShopExtension;
	if (name == "Armory") return BuildingType::Armory;
	if (name == "ArmoryExtension") return BuildingType::ArmoryExtension;
	if (name == "Farm") return BuildingType::Farm;
	if (name == "Pasture") return BuildingType::Pasture;
	if (name == "SheepPasture") return BuildingType::SheepPasture;
	if (name == "Field") return BuildingType::Field;
	if (name == "CottonField") return BuildingType::CottonField;
	if (name == "TradingWarehouse") return BuildingType::TradingWarehouse;
	if (name == "WarehouseExtension") return BuildingType::WarehouseExtension;
	if (name == "Warehouse") return BuildingType::Warehouse;
}

ResourseType Button::getResourceType()
{
	if (name == "RawWood") return ResourseType::RawWood;
	if (name == "ProcessedWood") return ResourseType::ProcessedWood;
	if (name == "Plank") return ResourseType::Plank;
	if (name == "Ore") return ResourseType::Ore;
	if (name == "PreciousOre") return ResourseType::PreciousOre;
	if (name == "Coal") return ResourseType::Coal;
	if (name == "Stone") return ResourseType::Stone;
	if (name == "Metal") return ResourseType::Metal;
	if (name == "PreciousMetal") return ResourseType::PreciousMetal;
	if (name == "Machine") return ResourseType::Machine;
	if (name == "Rail") return ResourseType::Rail;
	if (name == "Beam") return ResourseType::Beam;
	if (name == "Weapon") return ResourseType::Weapon;
	if (name == "Jewelry") return ResourseType::Jewelry;
	if (name == "Cereal") return ResourseType::Cereal;
	if (name == "Meat") return ResourseType::Meat;
	if (name == "Cotton") return ResourseType::Cotton;
}

std::string Button::getName()
{
	return name;
}