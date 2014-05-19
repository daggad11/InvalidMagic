//header file for creature
#ifndef CREATURE_H
#define CREATURE_H
#include <map>
#include "entity.hpp"

class Creature : public Entity
{
public:
	Creature();
	Creature(sf::RenderWindow* window, int width, int height, int x, int y, int mass, std::map<int, std::map<int, Entity*>>* entitymap);
	~Creature();
protected:
	std::map<std::string, int> stat;
};
#endif
