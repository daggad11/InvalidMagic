#include "creature.hpp"

Creature::Creature() {
	//todo
}

Creature::Creature(sf::RenderWindow* window, int width, int height, int x, int y, std::map<int, std::map<int, Entity*>>* entitymap, sf::Clock* timer) : Entity(window, width, height, x, y, entitymap) {
	this->timer = timer;
	stat["speed"] = 10; //tiles per second
	stat["dexterity"] = 10;
	stat["stamina"] = 10;
	stat["health"] = 10;
}

void Creature::setStat(std::string type, int newValue){
	stat[type] = newValue;
}

Creature::~Creature(){
	//todo
}
