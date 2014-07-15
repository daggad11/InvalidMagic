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
	enum StatName { SPEED, HEALTH, ATTACK, DEFENSE, BASEDAMAGE, DETECTIONRANGE, ATTACKTIME};

	Creature(); //default constructor
	Creature(sf::Clock* timer, int tileSize, sf::Vector2i position, sf::Vector2i size, std::vector<std::vector<Entity*> >* entityMap, TileMap* tileMap, sf::Texture* texture); //passes everything to entity
	std::map<int, float> getStats();
	std::map<int, float> stats;
protected:
	float nextMove; //used to limit creature movemetn
	float nextAttack; //used to limit creature attacking
	float damagedAt; //time at which creature was damaged

	sf::Font font;
	sf::Text damageText;

	float calculateDamage(std::map<int, float> attackerStats, std::map<int, float> defenderStats); //calculates damage between to creatures based off of stats
	
	 //mapping enumerated stats to their values for easy access
	sf::Clock* timer;
};

#endif