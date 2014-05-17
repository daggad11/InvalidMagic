//header file for creature
#ifndef CREATURE_H
#define CREATURE_H
#include <map>
#include "entity.hpp"

class Creature : public Entity
{
public:
	Creature();
	Creature(sf::RenderWindow* window, int width, int height, int x, int y, sf::Texture* texture, int mass);
	~Creature();
protected:
	std::map<std::string, int> stat;
};
#endif
