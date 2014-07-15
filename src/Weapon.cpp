#include "Weapon.hpp"

////////////////////
//PUBLIC FUNCTIONS//
////////////////////

Weapon::Weapon() {
	type = Type::MELEE;
	name = "Unarmed";
	hitTime = 0.5;

	statModifiers[StatName::ATTACK] = 2;
	statModifiers[StatName::BASEDAMAGE] = 3;
}

std::map<int, float> Weapon::getStatModifiers() {
	return statModifiers;
}

float Weapon::getHitTime() {
	return hitTime;
}

bool Weapon::getType() {
	return type;
}