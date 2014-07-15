#ifndef NPC_HPP
#define NPC_HPP
#include <cstdlib>
#include "Creature.hpp"

class Player;

class NPC : public Creature {
public:
	static int lastId;
	enum Type { PASSIVE, NONE, FOLLOW, MELEE }; //update and attack types

	NPC(int id, int updateType, int attackType, Player* player, std::map<int, float> stats, sf::Clock* timer, int tileSize, sf::Vector2i position, sf::Vector2i size, std::vector<std::vector<Entity*>>* entityMap, TileMap* tileMap, sf::Texture* texture);
	bool update(); //update called by world, selects correct update based off of type returns false if dead
	void passiveUpdate(); //update for passive npc's
	void followUpdate();
	void attack(); //attacks the player based on attackType
	void meleeAttack();
	void takeDamage(float damage);
private:
	int id; //used for deletion
	int attackType; //tells what type of attack to do
	int updateType; //tells what type of update to do
	float originalHealth; //used for healthbar

	sf::RectangleShape healthBar[2]; //healthbars, background and foreground

	Player* player; //pointer to player for reference

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //allows for drawing of healthbar
};

#endif