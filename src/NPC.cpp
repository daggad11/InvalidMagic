#include "NPC.hpp"
#include "Player.hpp"
#include <iostream>

////////////////////
//PUBLIC FUNCTIONS//
////////////////////
int NPC::lastId = 0;

NPC::NPC(int id, int updateType, int attackType, Player* player, std::map<int, float> stats, sf::Clock* timer, int tileSize, sf::Vector2i position, sf::Vector2i size, std::vector<std::vector<Entity*>>* entityMap, TileMap* tileMap, sf::Texture* texture) : Creature(timer, tileSize, position, size, entityMap, tileMap, texture) {
	this->id = id;
	this->updateType = updateType;
	this->attackType = attackType;
	this->stats = stats;
	this->player = player;

	originalHealth = stats[StatName::HEALTH];

	//loading rectangles for healthbar
	healthBar[0] = sf::RectangleShape(sf::Vector2f(size.x*tileSize, tileSize/10.0));
	healthBar[1] = sf::RectangleShape(sf::Vector2f(size.x*tileSize, tileSize/10.0));

	//setting color of healthbars
	healthBar[0].setFillColor(sf::Color::Black);
	healthBar[1].setFillColor(sf::Color::Red);

	//placing healthbars above npc's heads
	healthBar[0].setPosition(sf::Vector2f(position.x*tileSize, position.y*tileSize - healthBar[0].getSize().y - 5));
	healthBar[1].setPosition(sf::Vector2f(position.x*tileSize, position.y*tileSize - healthBar[0].getSize().y - 5));

	//incrementing last id
	lastId++;

	srand(time(NULL));
}

bool NPC::update() {
	//setting font
	damageText.setFont(font);

	//returning false if dead;
	if (stats[StatName::HEALTH] <= 0) {
		removeFromMap();
		return false;
	}

	if (updateType == Type::PASSIVE)
		passiveUpdate();
	if (updateType == Type::FOLLOW)
		followUpdate();

	return true;
}

void NPC::passiveUpdate() {
	if (timer->getElapsedTime().asSeconds() > nextMove) {

		bool hasMoved;

		//randomly choosing a direction to move in
		if (rand() % 4 == Direction::RIGHT)
			hasMoved = move(sf::Vector2i(1, 0));
		else if (rand() % 4 == Direction::LEFT) 
			hasMoved = move(sf::Vector2i(-1, 0));
		else if (rand() % 4 == Direction::UP)
			hasMoved = move(sf::Vector2i(0, -1));
		else
			hasMoved = move(sf::Vector2i(0, 1));

		//reseting move timer if npc has moved
		if (hasMoved) {
			nextMove = timer->getElapsedTime().asSeconds() + 1 - stats[StatName::SPEED] / 1000.0;

			//repositioning healthbars
			healthBar[0].setPosition(sf::Vector2f(position.x*tileSize, position.y*tileSize - healthBar[0].getSize().y - 5));
			healthBar[1].setPosition(sf::Vector2f(position.x*tileSize, position.y*tileSize - healthBar[0].getSize().y - 5));
		}
	}
}

void NPC::followUpdate() {
	if (timer->getElapsedTime().asSeconds() > nextMove) {
		bool hasMoved;
		sf::Vector2i distance = player->getPosition() - position;

		//attacking if close enough
		if (abs(distance.x) + abs(distance.y) <= 1) {
			
			//changing direction to attack direction
			if (distance.x > 0)
				direction = Direction::RIGHT;
			else if (distance.x < 0)
				direction = Direction::LEFT;
			else if (distance.y > 0)
				direction = Direction::DOWN;
			else if (distance.y < 0)
				direction = Direction::UP;
			updateVertices();

			attack();
			return;
		}

		//moving toward player if close enough
		if (abs(distance.x) + abs(distance.y) < stats[StatName::DETECTIONRANGE]) {

			//randomly chosing whether to move vertically or horizontally
			if (rand() % 2 == 0) { //HORIZONTAL
				if (player->getPosition().x > position.x) {
					hasMoved = move(sf::Vector2i(1, 0));

					//attempting to move around obsticles
					if (!hasMoved && player->getPosition().x > position.x + 1)
						hasMoved = move(sf::Vector2i(0, 1));
					if (!hasMoved && player->getPosition().x > position.x + 1)
						hasMoved = move(sf::Vector2i(0, -1));
				}
				else if (player->getPosition().x < position.x) {
					hasMoved = move(sf::Vector2i(-1, 0));

					//attempting to move around obsticles
					if (!hasMoved && player->getPosition().x < position.x - 1)
						hasMoved = move(sf::Vector2i(0, 1));
					if (!hasMoved && player->getPosition().x < position.x - 1)
						hasMoved = move(sf::Vector2i(0, -1));
				}
			}
			else { //VERTICAL
				if (player->getPosition().y > position.y) {
					hasMoved = move(sf::Vector2i(0, 1));

					//attempting to move around obsticles
					if (!hasMoved && player->getPosition().y > position.y + 1)
						hasMoved = move(sf::Vector2i(1, 0));
					if (!hasMoved && player->getPosition().y > position.y + 1)
						hasMoved = move(sf::Vector2i(-1, 0));
				}
				else if (player->getPosition().y < position.y) {
					hasMoved = move(sf::Vector2i(0, -1));

					//attempting to move around obsticles
					if (!hasMoved && player->getPosition().y < position.y -1)
						hasMoved = move(sf::Vector2i(1, 0));
					if (!hasMoved && player->getPosition().y < position.y -1)
						hasMoved = move(sf::Vector2i(-1, 0));
				}
			} //end of movement


			if (hasMoved) {
				nextMove = timer->getElapsedTime().asSeconds() + 0.3 - stats[StatName::SPEED] / 1000.0;

				//repositioning healthbars
				healthBar[0].setPosition(sf::Vector2f(position.x*tileSize, position.y*tileSize - healthBar[0].getSize().y - 5));
				healthBar[1].setPosition(sf::Vector2f(position.x*tileSize, position.y*tileSize - healthBar[0].getSize().y - 5));	

				//repositioning damage text
				damageText.setPosition(position.x * tileSize + tileSize/3, position.y * tileSize + 20);
			}
		}
		//passive movement if no player
		else {
			passiveUpdate();		
		}
	}	
}

void NPC::attack() {
	if (timer->getElapsedTime().asSeconds() >= nextAttack) {
		if (attackType == Type::MELEE)
			meleeAttack();
		nextAttack = timer->getElapsedTime().asSeconds() + stats[StatName::ATTACKTIME];
	}
}

void NPC::meleeAttack() {
	player->takeDamage(calculateDamage(stats, player->getStats()));
}

void NPC::takeDamage(float damage) {
	stats[StatName::HEALTH] -= damage;

	//resizing healthbar
	healthBar[1].setSize(sf::Vector2f(size.x * (stats[StatName::HEALTH] / originalHealth) * tileSize, healthBar[1].getSize().y));

	//updating damage text && setting damagedat
	damageText.setString(std::to_string((int)damage));
	damagedAt = timer->getElapsedTime().asSeconds();
}


/////////////////////
//Private FUNCTIONS//
/////////////////////
void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (stats.find(StatName::HEALTH)->second < originalHealth) {
		target.draw(healthBar[0]);
		target.draw(healthBar[1]);
	}

	states.texture = texture;
	target.draw(vertices, states);

	if (timer->getElapsedTime().asSeconds() < damagedAt + 0.25) {
		target.draw(damageText);
	}

}