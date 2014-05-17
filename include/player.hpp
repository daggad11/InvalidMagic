//header file for player
#ifndef PLAYER_H
#define PLAYER_H
#include "creature.hpp"

class Player : public Creature
{
public:
	Player(sf::RenderWindow *window, int width, int height, int x, int y, sf::Texture *texture, int mass);
	~Player();
private:
};
#endif
