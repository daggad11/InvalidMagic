//header file for the object object
#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>
#include "entity.hpp"

class Object : public Entity
{
public:
	Object();

	~Object();
private:
	sf::Sprite sprite;
	sf::Texture texture;
};
#endif