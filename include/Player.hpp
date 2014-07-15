#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <vector>
#include "Creature.hpp"
#include "NPC.hpp"
#include "Weapon.hpp"

class Player : public Creature {
public:
	Player(); //default constructor
	Player(std::vector<NPC>* npcs, sf::Clock* timer, int tileSize, sf::Vector2i position, sf::Vector2i size, std::vector<std::vector<Entity*>>* entityMap, TileMap* tileMap, sf::Texture* texture); //passes most things to creature
	void update(); //deals with moving the player, attacking, etc
	void setMoving(bool right, bool left, bool up, bool down); //sets smooth movement variables
	void setAttacking(int direction, bool value);
	void takeDamage(float damage); //decreases health
	std::map<int, float> getBaseStats(); //returns base stats
private:
	bool moving[4]; //used for smooth movement
	bool attacking[4]; //used for attacking in a direction
	std::map<int, float> baseStats; //base stats before buffs or nerfs
	std::vector<NPC>* npcs; //used to attack creatures

	Weapon weapon; //weapon used in combat;

	void resetStats(); //resets stats to base stats
	void equipWeapon(Weapon weapon);
	bool meleeAttack(sf::Vector2i position); //attacks npc at specifiec point
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //allows for drawing of healthbar
};

#endif