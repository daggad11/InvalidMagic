//header file for creature
#ifndef CREATURE_H
#define CREATURE_H

class Creature : public Entity
{
public:
	Creature(sf::RenderWindow *window, int width, int height, int x, int y, sf::Texture *texture, int mass);
	~Creature();
private:
	
};
#endif
