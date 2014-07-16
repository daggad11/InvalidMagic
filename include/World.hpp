#ifndef WORLD_HPP
#define WORLD_HPP
#include <cstdlib>
#include "TileMap.hpp"
#include "Entity.hpp"
#include "Creature.hpp"
#include "Player.hpp"
#include "NPC.hpp"

/*The world class contains everything that will
be drawn and that have 'physical properties'.
It also contains generation algorithms to create
random tilemaps and creatures.*/

class World : public sf::Drawable {
public:
	World(sf::Clock* timer, sf::View* view); //constructor only needs timer to pass on
	void update(); //updates all entities
	Player* getPlayer(); //returns pointer to player
private:
	enum EntityType { PLAYER, ZOMBIE, TREE };
	enum Direction { HORIZONTAL, VERTICAL };

	sf::Clock* timer; //passed down to npc's and player
	sf::View* view;
	std::map<int, sf::Texture> textures; //allows for access of specific textures

	TileMap tileMap; //map of all the current tiles
	std::vector<std::vector<Entity*>> entityMap; //vector representing entities on tileMap

	Player player; //the player the user plays as
	std::vector<Entity> objects; //decoration entites like trees, rocks, etc
	std::vector<NPC> npcs;

	void genMap(int width, int height); //generates a tilemap based off of a width and height
	void genForest(sf::Vector2i startPosition, sf::Vector2i size, int density); //creates a forest in a given area
	void paint(sf::Vector2i startPosition, sf::Vector2i size, int type); //generates road 0 = vertical 1 = horizontal
	void createNPC(sf::Vector2i position, int type); //creates an npc 
	void createObject(sf::Vector2i position, int type); //creates an object
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //draws all entities and tilemap
	bool mapClear(sf::Vector2i position, sf::Vector2i size); //checks if entityMap is empty and in bounds for a given area
};

#endif