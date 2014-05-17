//header file for the object object object object
#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>
#include "entity.hpp"

class Object : public Entity
{
public:
	Object();
	Object(sf::RenderWindow* window, int width, int height, int x, int y, sf::Texture* texture, std::string type);
	bool getSolid();
	void setSolid(bool s);
	bool getMovable();
	void setMovable(bool m);
	//void breakThisObject(int reducedBy);//this method takes in the players damage as an arg and decreases durability until it hits 0.
	~Object();
private:
	bool movable;
	bool solid;
	std::string type;
	int durability;//for if you want to smash it?
};
#endif
