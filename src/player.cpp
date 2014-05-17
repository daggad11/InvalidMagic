#include "player.hpp"
#include <iostream>

Player::Player() {
	//todo
}

Player::Player(sf::RenderWindow* window, int width, int height, int x, int y, sf::Texture* texture, int mass, sf::View* view) : Creature(window, width, height, x, y, texture, mass) {
	this->view = view;

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
	sprite.setPosition(x*Tile::tileSize, y*Tile::tileSize);
	view->setCenter(x*Tile::tileSize, y*Tile::tileSize);
	window->setView(*view);
}

void Player::setMovementState(bool up, bool down, bool right, bool left) {
	moveUp = up;
	moveDown = down;
	moveRight = right;
	moveLeft = left;
}

void Player::update(double time, std::map<int, std::map<int, Entity*>> &tilemap) {
	moveTimer += time;
	if ((moveUp || moveDown || moveLeft || moveRight) && moveTimer >= 0.1-stat["speed"]/2000) {
		tilemap[x][y] = NULL;
		move();
		moveTimer = 0;
		tilemap[x][y] = this;
	}
}
