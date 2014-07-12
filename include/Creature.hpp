#ifndef CREATURE_HPP
#define CREATURE_HPP
#include <map>
#include "Entity.hpp"

/*Creatures are children of entities that have stats
such as health, speed, etc. They each have an update
function that does different things based on thier
type.*/

class Creature : public Entity {
public:
	enum StatName { SPEED };

	Creature(); //default constructor
	Creature(sf::Clock* timer, int tileSize, sf::Vector2i position, sf::Vector2i size, std::vector<std::vector<Entity*>>* entityMap, TileMap* tileMap, sf::Texture* texture); //passes everything to entity
protected:
	float nextMove; //used to limit creature
	
	std::map<int, float> stats; //mapping enumerated stats to their values for easy access
	sf::Clock* timer;
};

#endif