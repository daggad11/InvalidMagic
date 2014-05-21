#include "player.hpp"
#include <iostream>

Player::Player() {
	//todo
}

Player::Player(sf::RenderWindow* window, int width, int height, int x, int y, sf::View* view, std::map<int, std::map<int, Entity*>>* entitymap, sf::Clock* timer) : Creature(window, width, height, x, y, entitymap, timer) {
	this->view = view;

	moveUp = false;
	moveDown = false;
	moveRight = false;
	moveLeft = false;
	moveTimer = 0;
	dataType = "player";
	texture = Resources::getTexture("player");
	initSprite();
	(*entitymap)[x][y] = this;
}

Player::~Player() {
	//todo
}

void Player::move(std::map<int, std::map<int, Entity*>>* entitymap) {
	if (moveUp && (*entitymap)[x][y-1] == NULL)
		y--;
	if (moveDown && (*entitymap)[x][y+1] == NULL)
		y++;
	if (moveRight && (*entitymap)[x+1][y] == NULL)
		x++;
	if (moveLeft && (*entitymap)[x-1][y] == NULL)
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

void Player::update() {
	moveTimer += timer->getElapsedTime().asSeconds();
	if ((moveUp || moveDown || moveLeft || moveRight) && moveTimer >= 1.0/(float)stat["speed"]) {
		(*entitymap)[x][y] = NULL;
		move(entitymap);
		moveTimer = 0;
		(*entitymap)[x][y] = this;
	}
}
