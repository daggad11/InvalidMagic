#ifndef WORLD_HPP
#define WORLD_HPP
#include <cstdlib>
#include "TileMap.hpp"
#include "Entity.hpp"
#include "Player.hpp"

/*The world class contains everything that will
be drawn and that have 'physical properties'.
It also contains generation algorithms to create
random tilemaps and creatures.*/

class World : public sf::Drawable {
public:
	World(sf::Clock* timer); //constructor only needs timer to pass on
	void update(); //updates all entities
	Player* getPlayer(); //returns pointer to player
private:
	enum Texture { PLAYER, TREE };

	sf::Clock* timer; //passed down to npc's and player
	std::map<int, sf::Texture> textures; //allows for access of specific textures

	TileMap tileMap; //map of all the current tiles
	std::vector<std::vector<Entity*>> entityMap; //vector representing entities on tileMap

	Player player; //the player the user plays as
	std::vector<Entity> objects; //decoration entites like trees, rocks, etc

	void genMap(int width, int height); //generates a tilemap based off of a width and height
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //draws all entities and tilemap
};

#endif