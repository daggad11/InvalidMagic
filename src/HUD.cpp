#include "HUD.hpp"
#include <iostream>

HUD::HUD(Player* player, sf::View* view, sf::RenderWindow* window) {
	this->player = player;
	this->view = view;
	this->window = window;

	//setting position && size of healthbars
	healthBar[0].setSize(sf::Vector2f(128, 16));
	healthBar[1].setSize(sf::Vector2f(128, 16));

	healthBar[0].setPosition(view->getCenter().x + view->getSize().x/4 - 128, view->getCenter().y - view->getSize().y);
	healthBar[1].setPosition(view->getCenter().x + view->getSize().x/4 - 128, view->getCenter().y - view->getSize().y);

	//setting color of healthbars
	healthBar[0].setFillColor(sf::Color::Black);
	healthBar[1].setFillColor(sf::Color::Red);
}

void HUD::update() {
	//setting healthbar to correct size
	healthBar[1].setSize(sf::Vector2f(128 * (player->getStats()[Player::StatName::HEALTH] / player->getBaseStats()[Player::StatName::HEALTH]), 16));

	//repositioning healthbar
	healthBar[0].setPosition(view->getCenter().x + view->getSize().x/2 - 128, view->getCenter().y - view->getSize().y/2);
	healthBar[1].setPosition(view->getCenter().x + view->getSize().x/2 - 128, view->getCenter().y - view->getSize().y/2);
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(healthBar[0]);
	target.draw(healthBar[1]);
}
