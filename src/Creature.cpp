#include "Creature.hpp"
#include <iostream>

////////////////////
//PUBLIC FUNCTIONS//
////////////////////

Creature::Creature() { 
	//does nothing
}

Creature::Creature(sf::Clock* timer, int tileSize, sf::Vector2i position, sf::Vector2i size, std::vector<std::vector<Entity*> >* entityMap, TileMap* tileMap, sf::Texture* texture) : Entity(tileSize, position, size, entityMap, tileMap, texture) {
	this->timer = timer;

	//setting type to creature
	type = Type::CREATURE;

	//setting move timer
	nextMove = timer->getElapsedTime().asSeconds();
	nextAttack = timer->getElapsedTime().asSeconds();

	//loading font and text
	font.loadFromFile("resources/stocky.ttf");	
	damageText = sf::Text("", font, 20);
	damageText.setColor(sf::Color::Red);
}

std::map<int, float> Creature::getStats() {
	return stats;
}

/////////////////////
//PRIVATE FUNCTIONS//
/////////////////////

float Creature::calculateDamage(std::map<int, float> attackerStats, std::map<int, float> defenderStats) {
	int damage;

	//calculating actual damage
	damage = (int)(attackerStats[StatName::ATTACK] / defenderStats[StatName::DEFENSE] * attackerStats[StatName::BASEDAMAGE] + (rand() % (int)attackerStats[StatName::BASEDAMAGE]));

	//calculating block chance
	if (defenderStats[StatName::DEFENSE] / attackerStats[StatName::ATTACK] * (rand() % 100) >= 100)
		damage = 0;

	return (float)damage;
}
