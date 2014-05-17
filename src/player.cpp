#include "player.hpp"

Player::Player(sf::RenderWindow* window, int width, int height, int x, int y, sf::Texture* texture, int mass) : Creature(window, width, height, x, y, texture, mass) {
	moveUp = false;
	moveDown = false;
	moveRight = false;
	moveLeft = false;
}

Player::~Player() {
	//todo
}

void Player::move() {
	if (moveUp)
		y--;
	if (moveDown)
		y++;
	if (moveRight)
		x++;
	if (moveLeft)
		x--;
}

void Player::setMovementState(bool up, bool down, bool right, bool left) {
	moveUp = up;
	moveDown = down;
	moveRight = right;
	moveLeft = left;
}
