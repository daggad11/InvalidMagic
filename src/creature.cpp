#include "creature.hpp"

Creature::Creature() {
	//todo
}

Creature::Creature(sf::RenderWindow* window, int width, int height, int x, int y, std::map<int, std::map<int, Entity*>>* entitymap, sf::Clock* timer) : Entity(window, width, height, x, y, entitymap) {
	this->timer = timer;
	stat["speed"] = 10; //tiles per second
}

Creature::~Creature(){
	//todo
}
