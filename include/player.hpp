//header file for player
#ifndef PLAYER_H
#define PLAYER_H
#include "creature.hpp"

class Player : public Creature
{
public:
	Player();
	Player(sf::RenderWindow* window, int width, int height, int x, int y, sf::Texture* texture, int mass);
	~Player();
	void setMovementState(bool up, bool down, bool right, bool left);
private:
	bool moveUp;
	bool moveDown;
	bool moveRight;
	bool moveLeft;

	void move();
};
#endif
