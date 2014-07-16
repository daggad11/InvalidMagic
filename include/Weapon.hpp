#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <map>

class Weapon {
public:
	enum Type { MELEE, RANGED };
	enum StatName { SPEED, HEALTH, ATTACK, DEFENSE, BASEDAMAGE };

	Weapon();
	Weapon(std::string name, bool type, std::map<int, float> statModifiers, float hitTime);
	std::map<int, float> getStatModifiers();
	float getHitTime();
	bool getType();
	std::string getName();
private:
	bool type; //type of weapon, melee or ranged
	std::string name; //name of weapon
	std::map<int, float> statModifiers; //modifiers to player stats
	float hitTime; //amount of time between attacks
};

#endif