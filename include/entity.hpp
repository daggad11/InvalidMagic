//this is the header file for the entities
#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity();
	Entity(sf::RenderWindow* window, int width, int height, int x, int y, sf::Texture* texture, int mass);
	~ Entity();
protected:
	sf::RenderWindow *window;
	sf::Sprite sprite;
	int width;
	int height;
	int x;
	int y;
	int mass;
};
#endif
