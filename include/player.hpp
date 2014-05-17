//header file for player
#ifndef PLAYER_H
#define PLAYER_H
#include "creature.hpp"

class Player : public Creature
{
public:
	Player();
	Player(sf::RenderWindow* window, int width, int height, int x, int y, sf::Texture* texture, int mass, sf::View* view);
	~Player();
	void update(double time);
	
	//setters
	void setMovementState(bool up, bool down, bool right, bool left);
private:
	sf::View* view;
	bool moveUp;
	bool moveDown;
	bool moveRight;
	bool moveLeft;

	//timers
	double moveTimer;

	//stats
	int speed;

	void move();
};
#endif
