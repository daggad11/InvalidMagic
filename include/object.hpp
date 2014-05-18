//header file for the object object object object
#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>
#include "entity.hpp"

class Object : public Entity
{
public:
	Object();
	Object(sf::RenderWindow* window, int width, int height, int x, int y, sf::Texture* texture, std::string type, std::map<int, std::map<int, Entity*>>* tilemap);
	bool getSolid();
	void setSolid(bool s);
	int getDurability();
	void setDurability(int newDur);
	std::string getType();
	void setType(std::string t);
	void breakThisObject(int reducedBy);//this method takes in the players damage as an arg and decreases durability until it hits 0.
	~Object();
private:
	bool movable;
	bool solid;
	std::string type;
	int durability;//for if you want to smash it?
};
#endif
