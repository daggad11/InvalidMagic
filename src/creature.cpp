#include "creature.hpp"

Creature::Creature() {
	//todo
}

Creature::Creature(sf::RenderWindow* window, int width, int height, int x, int y, std::map<int, std::map<int, Entity*>>* entitymap) : Entity(window, width, height, x, y, entitymap) {
	stat["speed"] = 1;
}

Creature::~Creature(){
	//todo
}
