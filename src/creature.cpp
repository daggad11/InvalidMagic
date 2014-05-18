#include "creature.hpp"

Creature::Creature() {
	//todo
}

Creature::Creature(sf::RenderWindow* window, int width, int height, int x, int y, sf::Texture* texture, int mass, std::map<int, std::map<int, Entity*>>* tilemap) : Entity(window, width, height, x, y, texture, mass, tilemap) {
	stat["speed"] = 1;
}

Creature::~Creature(){
	//todo
}
