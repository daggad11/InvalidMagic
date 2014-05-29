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
	Entity(sf::RenderWindow* window, int width, int height, int x, int y, std::map<int, std::map<int, Entity*>>* entitymap);
	~ Entity();
	void draw();

	//getters
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	int getDataType();
	virtual void update() = 0;
protected:
	sf::RenderWindow* window;
	sf::Texture* texture;
	std::map<int, std::map<int, Entity*>>* entitymap;
	sf::Sprite sprite;
	int width;
	int height;
	int x;
	int y;
	int dataType;
	enum EntityType {
		entity,
		object,
		player,
		npc,
		creature
	};
	void initSprite();
	void removeFromMap();
	void updateOnMap();
	bool isClear(int x1, int y1, int x2, int y2);
};
#endif
