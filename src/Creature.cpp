#include "Creature.hpp"

////////////////////
//PUBLIC FUNCTIONS//
////////////////////

Creature::Creature() { 
	//does nothing
}

Creature::Creature(sf::Clock* timer, int tileSize, sf::Vector2i position, sf::Vector2i size, std::vector<std::vector<Entity*>>* entityMap, TileMap* tileMap, sf::Texture* texture) : Entity(tileSize, position, size, entityMap, tileMap, texture) {
	this->timer = timer;
}