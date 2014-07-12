#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Creature.hpp"

class Player : public Creature {
public:
	Player(); //default constructor
	Player(sf::Clock* timer, int tileSize, sf::Vector2i position, sf::Vector2i size, std::vector<std::vector<Entity*>>* entityMap, TileMap* tileMap, sf::Texture* texture); //passes most things to creature
	void update(); //deals with moving the player, attacking, etc
	void setMoving(bool right, bool left, bool up, bool down); //sets smooth movement variablesa
private:
	bool moving[4]; //used for smooth movement
};

#endif