#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"

/*Entities are top level objects that represent
something that is in existence in the world.
Entity is then divided into subclasses creature, and object. */

class Entity : public sf::Drawable {
public:
	enum Direction { RIGHT, LEFT, UP, DOWN };

	Entity(); //default constructor
	Entity(int tileSize, sf::Vector2i position, sf::Vector2i size, std::vector<std::vector<Entity*>>* entityMap, TileMap* tileMap, sf::Texture* texture); //constructor passes in needed variables
	sf::Vector2i getPosition(); //returns position
protected:
	int tileSize; //size of a tile in pixels
	int direction; //direction entity is facing

	sf::Vector2i position; //x and y pos in tilemap
	sf::Vector2i size; //size in terms of tiles

	std::vector<std::vector<Entity*>>* entityMap; //pointer to world's map of entity pointers
	TileMap* tileMap; //pointer to world's tilemap

	sf::VertexArray vertices; //vertices that entity will be drawn within
	sf::Texture* texture; //Texture to be drawn

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //allows entity to be drawn by window
	void updateVertices(); //changes vertices based off of position
	void changeTexturePosition(int x, int y); //selects a frame from the texture sheet based off of x and y location in terms of frames
	void placeOnMap(); //repositions entity on entitymap
	void removeFromMap(); //removes entity from entitymap at current position
	bool mapClear(sf::Vector2i newPosition); //checks if a position on entity map is clear
	bool move(sf::Vector2i deltaPosition); //moves entity's vertices and position on map 
};

#endif