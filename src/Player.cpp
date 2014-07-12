#include "Player.hpp"

////////////////////
//PUBLIC FUNCTIONS//
////////////////////

Player::Player() {
	//does nothing
}

Player::Player(sf::Clock* timer, int tileSize, sf::Vector2i position, sf::Vector2i size, std::vector<std::vector<Entity*>>* entityMap, TileMap* tileMap, sf::Texture* texture) : Creature(timer, tileSize, position, size, entityMap, tileMap, texture) {
	
	//setting smooth movement variables to false
	for (int a = 0; a < 4; a++) {
		moving[a] = false;
	}

	//setting stats
	stats[StatName::SPEED] = 1;
}

void Player::update() {
	if (timer->getElapsedTime().asSeconds() > nextMove) {
		sf::Vector2i deltaPosition(0, 0);

		//adding 1 to position if key is pressed
		if (moving[Direction::RIGHT])
			deltaPosition.x += 1;
		if (moving[Direction::LEFT])
			deltaPosition.x -= 1;

		//preventing diagonal movement
		if (!moving[Direction::RIGHT] && !moving[Direction::LEFT]) {
			if (moving[Direction::UP])
				deltaPosition.y -= 1;
			if (moving[Direction::DOWN])
				deltaPosition.y += 1;
		}

		//attempting to move if position should be changed
		if (deltaPosition.x != 0 || deltaPosition.y != 0)
			if (move(deltaPosition))
				//resetting move timer since player has moved. amount reset based off of speed
				nextMove = timer->getElapsedTime().asSeconds() + 0.25 - stats[StatName::SPEED] / 1000.0;

	}
}

void Player::setMoving(bool right, bool left, bool up, bool down) {
	moving[Direction::RIGHT] = right;
	moving[Direction::LEFT] = left;
	moving[Direction::UP] = up;
	moving[Direction::DOWN] = down;
}