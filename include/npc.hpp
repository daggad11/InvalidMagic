#ifndef NPC_H
#define NPC_H
#include <cstdlib>
#include "creature.hpp"

class NPC : public Creature
{
public:
	NPC(sf::RenderWindow* window, int width, int height, int x, int y, std::map<int, std::map<int, Entity*>>* entitymap, sf::Clock* timer);
	~NPC();
	void update();
private:
	double moveTimer;
	double moveTime;
};
#endif
