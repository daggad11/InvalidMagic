#include "Weapon.hpp"

////////////////////
//PUBLIC FUNCTIONS//
////////////////////

Weapon::Weapon() {
	//do nothing
}

Weapon::Weapon(std::string name, bool type, std::map<int, float> statModifiers, float hitTime) {
	this->name = name;
	this->type = type;
	this->statModifiers = statModifiers;
	this->hitTime = hitTime;
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

std::string Weapon::getName() {
	return name;
}