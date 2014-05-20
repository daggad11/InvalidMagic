//header file for creature
#ifndef CREATURE_H
#define CREATURE_H
#include <map>
#include "entity.hpp"

class Creature : public Entity
{
public:
	Creature();
	Creature(sf::RenderWindow* window, int width, int height, int x, int y, std::map<int, std::map<int, Entity*>>* entitymap, sf::Clock* timer);
	~Creature();
	virtual void update()=0;
	void setStat(std::string type, int newValue);
protected:
	sf::Clock* timer;
	std::map<std::string, int> stat;
};
#endif
