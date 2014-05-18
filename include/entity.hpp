//this is the header file for the entities
#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <map>
#include "tile.hpp"
#include "resources.hpp"

class Entity
{
public:
	Entity();
	Entity(sf::RenderWindow* window, int width, int height, int x, int y, int mass, std::map<int, std::map<int, Entity*>>* tilemap);
	~ Entity();
	void draw();

	//getters
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	int getMass();
protected:
	sf::RenderWindow* window;
	sf::Texture* texture;
	std::map<int, std::map<int, Entity*>>* tilemap;
	sf::Sprite sprite;
	int width;
	int height;
	int x;
	int y;
	int mass;
	void initSprite();
};
#endif
