#include "Player.hpp"
#include <iostream>

////////////////////
//PUBLIC FUNCTIONS//
////////////////////

Player::Player() {
	//does nothing
}

Player::Player(std::vector<NPC>* npcs, sf::Clock* timer, int tileSize, sf::Vector2i position, sf::Vector2i size, std::vector<std::vector<Entity*>>* entityMap, TileMap* tileMap, sf::Texture* texture) : Creature(timer, tileSize, position, size, entityMap, tileMap, texture) {
	this->npcs = npcs;

	//setting smooth movement variables to false
	for (int a = 0; a < 4; a++) {
		moving[a] = false;
	}

	//setting attacking variables to false
	for (int a = 0; a < 4; a++) {
		attacking[a] = false;
	}

	//setting baseStats
	baseStats[StatName::SPEED] = 1;
	baseStats[StatName::HEALTH] = 400;
	baseStats[StatName::ATTACK] = 10;
	baseStats[StatName::DEFENSE] = 10;
	baseStats[StatName::BASEDAMAGE] = 10;

	//setting stats to baseStats
	resetStats();

	//creating Weapons
	std::map<int, float> statModifiers;
	statModifiers[StatName::ATTACK] = 3;
	statModifiers[StatName::BASEDAMAGE] = 5;

	weapons.push_back(Weapon("Unarmed", Weapon::Type::MELEE, statModifiers, 0.5));
	weapons.push_back(Weapon("Katana", Weapon::Type::MELEE, statModifiers, 0.5));
	weapons.push_back(Weapon("Mace", Weapon::Type::MELEE, statModifiers, 0.5));
	weapons.push_back(Weapon("Stick", Weapon::Type::MELEE, statModifiers, 0.5));

	//equiping unarmed weapon
	equipWeapon(weapons[0]);
}

void Player::update() {
	//setting font to avoid segfault
	damageText.setFont(font);

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
		if (deltaPosition.x != 0 || deltaPosition.y != 0) {
			if (move(deltaPosition)) {
				//resetting move timer since player has moved. amount reset based off of speed
				nextMove = timer->getElapsedTime().asSeconds() + 0.25 - stats[StatName::SPEED] / 1000.0;
				//repositioning damage text
				damageText.setPosition(position.x * tileSize + tileSize/3, position.y * tileSize + 20);
			}
		}
	} //end of movement

	//checking if attack cooldown in over
	if (timer->getElapsedTime().asSeconds() > nextAttack) {

		//ATTACKING RIGHT
		if (attacking[Direction::RIGHT]) {
			direction = Direction::RIGHT;
			updateVertices();

			//MELEE ATTACK
			if (equipedWeapon.getType() == Weapon::Type::MELEE) {
				if (meleeAttack(position+sf::Vector2i(1, 0)))
					nextAttack = timer->getElapsedTime().asSeconds() + equipedWeapon.getHitTime();
			}
		}
		//ATTACKING LEFT
		else if (attacking[Direction::LEFT]) {
			direction = Direction::LEFT;
			updateVertices();
			nextAttack = timer->getElapsedTime().asSeconds() + equipedWeapon.getHitTime();

			//MELEE ATTACK
			if (equipedWeapon.getType() == Weapon::Type::MELEE) {
				if (meleeAttack(position+sf::Vector2i(-1, 0)))
					nextAttack = timer->getElapsedTime().asSeconds() + equipedWeapon.getHitTime();
			}
		}
		//ATTACKING UP
		else if (attacking[Direction::UP]) {
			direction = Direction::UP;
			updateVertices();
			nextAttack = timer->getElapsedTime().asSeconds() + equipedWeapon.getHitTime();

			//MELEE ATTACK
			if (equipedWeapon.getType() == Weapon::Type::MELEE) {
				if (meleeAttack(position+sf::Vector2i(0, -1)))
					nextAttack = timer->getElapsedTime().asSeconds() + equipedWeapon.getHitTime();
			}
		}
		//ATTACKING DOWN
		else if (attacking[Direction::DOWN]) {
			direction = Direction::DOWN;
			updateVertices();
			nextAttack = timer->getElapsedTime().asSeconds() + equipedWeapon.getHitTime();

			//MELEE ATTACK
			if (equipedWeapon.getType() == Weapon::Type::MELEE) {
				if (meleeAttack(position+sf::Vector2i(0, 1)))
					nextAttack = timer->getElapsedTime().asSeconds() + equipedWeapon.getHitTime();
			}
		}
	} //end of attacking
}

void Player::setMoving(bool right, bool left, bool up, bool down) {
	moving[Direction::RIGHT] = right;
	moving[Direction::LEFT] = left;
	moving[Direction::UP] = up;
	moving[Direction::DOWN] = down;
}

void Player::setAttacking(int direction, bool value) {
	attacking[direction] = value;
}

void Player::takeDamage(float damage) {
	stats[StatName::HEALTH] -= damage;

	//updating damage text && setting damagedat
	damageText.setString(std::to_string((int)damage));
	damagedAt = timer->getElapsedTime().asSeconds();
}

std::map<int, float> Player::getBaseStats() {
	return baseStats;
}

std::vector<Weapon> Player::getWeapons() {
	return weapons;
}

Weapon Player::getEquipedWeapon() {
	return equipedWeapon;
}

/////////////////////
//Private FUNCTIONS//
/////////////////////

void Player::resetStats() {
	//looping through all basestats and setting stats equal to value
	for (auto baseStat : baseStats) {
		stats[baseStat.first] = baseStat.second;
	}
}

void Player::equipWeapon(Weapon weapon) {
	equipedWeapon = weapon;

	for (auto statModifier : weapon.getStatModifiers()) {
		stats[statModifier.first] = baseStats[statModifier.first] + statModifier.second;
	}
}

bool Player::meleeAttack(sf::Vector2i position) {
	for (int a = 0; a < (*npcs).size(); a++) {
		if ((*npcs)[a].getPosition() == position) {
			(*npcs)[a].takeDamage(calculateDamage(stats, (*npcs)[a].getStats()));
			return true;
		}
	}
	return false;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.texture = texture;
	target.draw(vertices, states);

	if (timer->getElapsedTime().asSeconds() < damagedAt + 0.25) {
		target.draw(damageText);
	}
}