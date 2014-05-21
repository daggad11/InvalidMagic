#ifndef NPC_H
#define NPC_H
#include <cstdlib>
#include <map>
#include "creature.hpp"

class NPC : public Creature
{
public:
	NPC(sf::RenderWindow* window, int width, int height, int x, int y, std::map<int, std::map<int, Entity*>>* entitymap, sf::Clock* timer, std::string type);
	~NPC();

	//update functions
	void update();
	void passiveUpdate();
	void cowUpdate();
	void wolfUpdate();
	void (NPC::*realUpdate)( );
private:
	double moveTimer;
	double moveTime;
	bool isAggro;
};
#endif
