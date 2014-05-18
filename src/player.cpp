#include "player.hpp"
#include <iostream>

Player::Player() {
	//todo
}

Player::Player(sf::RenderWindow* window, int width, int height, int x, int y, int mass, sf::View* view, std::map<int, std::map<int, Entity*>>* tilemap) : Creature(window, width, height, x, y, mass, tilemap) {
	this->view = view;

	moveUp = false;
	moveDown = false;
	moveRight = false;
	moveLeft = false;
	moveTimer = 0;
	
	texture = Resources::getTexture("player");
	initSprite();
	(*tilemap)[x][y] = this;
}

Player::~Player() {
	//todo
}

void Player::move(std::map<int, std::map<int, Entity*>>* tilemap) {
	if (moveUp && (*tilemap)[x][y-1] == NULL)
		y--;
	if (moveDown && (*tilemap)[x][y+1] == NULL)
		y++;
	if (moveRight && (*tilemap)[x+1][y] == NULL)
		x++;
	if (moveLeft && (*tilemap)[x-1][y] == NULL)
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

void Player::update(double time) {
	moveTimer += time;
	if ((moveUp || moveDown || moveLeft || moveRight) && moveTimer >= 0.1-stat["speed"]/2000) {
		(*tilemap)[x][y] = NULL;
		move(tilemap);
		moveTimer = 0;
		(*tilemap)[x][y] = this;
	}
}
