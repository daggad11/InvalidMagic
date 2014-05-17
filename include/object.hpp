//header file for the object object
#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>
#include "entity.hpp"

class Object : public Entity
{
public:
	Object();
	Object(sf::RenderWindow* window, int width, int height, int x, int y, sf::Texture* texture, int mass);
	~Object();
private:
	bool moveable;
};
#endif
